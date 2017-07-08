from flask import Flask, redirect, render_template, request, url_for

import helpers
import sys
import os
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)
        # instantiate analyzer
        # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzing = Analyzer(positives, negatives)

    # TODO
    positive, negative, neutral = 0.0, 0.0, 0.00
    if tweets == None:
        print("Enter different user, no tweets")
    else:
        for tweet in tweets:
            sentsum = 0
            for word in tweet.split():
                sentsum+=analyzing.analyze(word)
            if sentsum > 0.0:
                positive+=1.0
            elif sentsum < 0.0:
                negative+=1.0
            else:
                neutral+=1.0
                
    positive = positive/ 100.00
    negative = negative/100.00
    neutral = neutral/100.00

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
