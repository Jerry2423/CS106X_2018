#include "LineConstructor.h"
using namespace std;

namespace {
    /* Font to use for rendering. */
    const string kFont = GraphicsConstants::kBrowserFont + "-" + to_string(GraphicsConstants::kBrowserFontSize);

    /* Constructs a GLabel used for measuring text. This should not be called directly. */
    unique_ptr<GLabel> makeMeasuringLabel() {
        unique_ptr<GLabel> result(new GLabel(""));
        result->setFont(kFont);
        return result;
    }

    /* Returns the width of a given piece of text if it were to be rendered as a frame. */
    double widthOf(const string& text) {
        static unique_ptr<GLabel> measurer = makeMeasuringLabel();

        measurer->setLabel(text);
        return measurer->getWidth();
    }

    /* Flushes out the token being assembled, if any, and marks that there is no token being
     * assembled.
     */
    void flushFrame(vector<Frame *>& frames, const HTMLToken& current,
                    const GRectangle& bounds, bool& isCurrent) {
        if (isCurrent) {
            frames.push_back(new Frame(bounds.getX(), bounds.getY(), bounds.getWidth(), current));
            isCurrent = false;
        }
    }

    /* Given a sequence of HTML tokens, converts those tokens into a collection of
     * frames.
     */
    vector<Frame *> tokensToFrames(const vector<HTMLToken>& pageContents,
                                   double contentWidth) {
        double y = GraphicsConstants::kLineSpacing;
        double x = 0;

        vector<Frame* > result;
        HTMLToken  current;
        GRectangle currentBounds;

        bool isPrevious = false;
        for (auto& token: pageContents) {
            /* Newline: Move down to the next line. This flushes the current token. */
            if (token.text == "\n") {
                x = 0;
                y += GraphicsConstants::kParagraphSpacing;

                flushFrame(result, current, currentBounds, isPrevious);
                continue;
            }

            /* If the current token does not fit on this line, flush the existing token and
             * place this token on the next line.
             */
            double currWidth = widthOf(token.text);
            if (x + currWidth > contentWidth) {
                x = 0;
                y += GraphicsConstants::kLineSpacing;

                flushFrame(result, current, currentBounds, isPrevious);
            }

            /* If this token is whitespace and we're at the front of a line, skip this token. */
            if (isspace(token.text[0]) && int(x) == 0) {
                continue;
            }

            /* If there's a previous token, and we have the same attributes as it, we can merge. */
            if (isPrevious && current.attributes == token.attributes) {
                current.text += token.text;
                currentBounds = {
                    currentBounds.getX(), currentBounds.getY(),
                    currentBounds.getWidth() + currWidth,
                    currentBounds.getHeight()
                };
            }
            /* Otherwise, either there isn't a previous token, or we can't merge with it. Either
             * way, flush out what was there before and start a new token.
             */
            else {
                flushFrame(result, current, currentBounds, isPrevious);

                current = token;
                currentBounds = {
                    x,
                    y - GraphicsConstants::kLineSpacing,
                    currWidth,
                    GraphicsConstants::kLineSpacing
                };

                isPrevious = true;
            }

            x += currWidth;
        }

        /* Flush any remaining tokens. */
        flushFrame(result, current, currentBounds, isPrevious);
        return result;
    }

    /* Given a line of tokens, assembles them into a line and flushes them into the
     * result vector.
     */
    void flushLine(Vector<Line *>& result, vector<Frame *>& frames) {
        /* Assemble a new line. */
        auto line = new Line(frames.front()->y(),
                             frames.front()->y() + frames.front()->height());
        line->setFrames(frames);
        result += line;

        frames.clear();
    }

    /* Returns whether two doubles are close enough for our tolerance purposes. */
    bool aboutEqual(double lhs, double rhs) {
        static const double kEpsilon = 0.1;
        return fabs(lhs - rhs) <= kEpsilon;
    }

    /* Given a sequence of tokens, breaks those tokens apart into individual lines. */
    Vector<Line *> framesToLines(const vector<Frame *>& frames) {
        /* If there are no frames, there's nothing to do. */
        if (frames.empty()) return {};

        Vector<Line *>  result;
        vector<Frame *> thisLine;

        for (auto frame: frames) {
            /* If we can't extend this line, flush the current line. */
            if (!thisLine.empty() && !aboutEqual(thisLine.front()->y(), frame->y())) {
                flushLine(result, thisLine);
            }
            thisLine.push_back(frame);
        }

        if (!thisLine.empty()) flushLine(result, thisLine);
        return result;
    }
}

/* Frame layout logic. */
shared_ptr<LineManager> layOutPage(const vector<HTMLToken>& pageContents,
                                   double contentWidth) {
    return make_shared<LineManager>(framesToLines(tokensToFrames(pageContents, contentWidth)));
}

