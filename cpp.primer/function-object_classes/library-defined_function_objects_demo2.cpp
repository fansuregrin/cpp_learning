// Topic: Using a Library Function Object with the Algorithms
// 
// The function-object classes that represent operators are 
// often used to override the default operator used by an algorithm.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Score {
public:
    Score(int __eng_sc, int __math_sc):
    eng_score(__eng_sc), math_score(__math_sc) {}

    bool operator==(const Score& rhs) const {
        return eng_score == rhs.eng_score
            && math_score == rhs.math_score;
    }

    bool operator!=(const Score& rhs) const {
        return !(*this == rhs);
    }

    bool operator>(const Score& rhs) const {
        if (eng_score != rhs.eng_score) {
            return eng_score > rhs.eng_score;
        } else {
            return math_score > rhs.math_score;
        }
    }

    bool operator<(const Score& rhs) const {
        return !(*this == rhs || *this > rhs);
    }

    bool operator<=(const Score& rhs) const {
        return !(*this > rhs);
    }

    bool operator>=(const Score& rhs) const {
        return *this == rhs || *this > rhs;
    }

    friend ostream& operator<<(ostream&, const Score&);
private:
    int eng_score;
    int math_score;
};

ostream& operator<<(ostream& out, const Score& sc) {
    out << sc.eng_score << ", " << sc.math_score;
    return out;
}

int main() {
    vector<Score> scores = {
        {90, 88}, {98, 90}, {92, 81},
        {98, 78}, {92, 81}, {92, 77},
        {87, 99}, {78, 81}, {89, 88}
    };
    cout << "before sort" << endl;
    for (const auto& sc:scores) {
        cout << sc << endl;
    }
    cout << '\n';

    // sort `scores` in descedent order
    // 
    // To sort into descending order, we can pass an object of type `greater`. That class
    // generates a call operator that invokes the greater-than operator of the underlying
    // element type (in this case, i.e., `Score`).
    // 
    // pass a temporary funciton object that applies greater-than(>) operator to 
    // two `Score`s as the argument of `__comp`
    sort(scores.begin(), scores.end(), greater<Score>());
    cout << "after sort" << endl;
    for (const auto& sc:scores) {
        cout << sc << endl;
    }
    cout << '\n';
}