import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        self.pos = set()
        self.neg = set()
        
        pfile = open(positives)
        for line in pfile:
            self.pos.add(line.strip("\n"))
        pfile.close()
        
        nfile = open(negatives)
        for line in nfile:
            self.neg.add(line.strip("\n"))
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        if text in self.pos:
            return 1
        elif text in self.neg:
            return -1
        else:
            return 0
