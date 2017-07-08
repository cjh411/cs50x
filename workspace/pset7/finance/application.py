from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    purchHistory  = db.execute("SELECT stock, sum(shares) as shares FROM purch_history WHERE id = :id GROUP BY stock", id = session["user_id"])
    price = []
    holdings = 0
    user = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"] )
    for i in range(len(purchHistory)):
        values = lookup(purchHistory[i]['stock'])
        price.append((purchHistory[i]['stock'].upper(),purchHistory[i]['shares'],values['price'],values['price']*purchHistory[i]['shares']))
        holdings = holdings + values['price']*purchHistory[i]['shares']
    return render_template("index.html", stocks = price, cash = user[0]['cash'], holdings = holdings, total = user[0]['cash']+holdings)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        user = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"] )
        values = lookup(request.form.get("Symbol"))
        cost = values['price']*float(request.form.get("Shares"))
        if user[0]['cash'] < cost :
            return apology("You don't have enough money for this purchase")
        else:
            db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash = user[0]['cash']-cost, id = session["user_id"])
            db.execute("Insert INTO purch_history ('id','stock','price','shares') VALUES (:id,:stock,:price,:shares)",id = session["user_id"], stock = request.form.get("Symbol"), price = values['price'], shares = float(request.form.get("Shares")))
            return render_template("bought.html",result = values, shares = float(request.form.get("Shares")), cost = cost, cash = user[0]['cash'] - cost)
    else:
        return render_template("buy.html")
@app.route("/history")
@login_required
def history():
    
    purchHistory  = db.execute("SELECT * FROM purch_history WHERE id = :id", id = session["user_id"])

    return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        values = lookup(request.form.get("Symbol"))
        if values == None:
            return apology("ReEnter Symbol")
        else:
            return render_template("quoted.html",result = values)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # query database for username
    if request.method == "POST":
        if request.form.get("password")==request.form.get("confirm password"):
            db.execute("Insert INTO users ('username','hash') VALUES (:username,:pw)", username=request.form.get("username"),pw = pwd_context.encrypt(request.form.get("password")))
            rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
            session["user_id"] = rows[0]['id']
            return redirect(url_for("index"))
        else:
            return apology("Passwords Do Not Match")
    else:
        return render_template("register.html")
        
        
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        for j in range(2):
            purchHistory  = db.execute("SELECT stock, sum(shares) as shares FROM purch_history WHERE id = :id GROUP BY stock", id = session["user_id"])
            price = []
            holdings = 0
            user = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"] )
            for i in range(len(purchHistory)):
                values = lookup(purchHistory[i]['stock'])
                price.append((purchHistory[i]['stock'].upper(),purchHistory[i]['shares'],values['price'],values['price']*purchHistory[i]['shares']))
                holdings = holdings + values['price']*purchHistory[i]['shares']
                if j == 0:
                    if request.form.get("Symbol") == purchHistory[i]['stock']:
                        if 0<float(request.form.get("Shares")) <= purchHistory[i]['shares']:
                            db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash = user[0]['cash']+values['price']*float(request.form.get("Shares")), id = session["user_id"])
                            db.execute("Insert INTO purch_history ('id','stock','price','shares') VALUES (:id,:stock,:price,:shares)",id = session["user_id"], stock = request.form.get("Symbol"), price = values['price'], shares = -float(request.form.get("Shares")))
                        else:
                            return apology("Please change your shares to a correct number")
        return render_template("sold.html", stocks = price, cash = user[0]['cash'], holdings = holdings, total = user[0]['cash']+holdings)

    else:
        purchHistory  = db.execute("SELECT stock, sum(shares) as shares FROM purch_history WHERE id = :id GROUP BY stock", id = session["user_id"])
        price = []
        holdings = 0
        user = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"] )
        for i in range(len(purchHistory)):
            values = lookup(purchHistory[i]['stock'])
            price.append((purchHistory[i]['stock'].upper(),purchHistory[i]['shares'],values['price'],values['price']*purchHistory[i]['shares']))
            holdings = holdings + values['price']*purchHistory[i]['shares']
        return render_template("sell.html", stocks = price, cash = user[0]['cash'], holdings = holdings, total = user[0]['cash']+holdings)

