#ifndef QUERY_H
#define QUERY_H

#include "text_query.h"
#include <algorithm>
#include <iterator>

using namespace std;

class Query;

// private, abstract class acts as a base class for concrete query types
class QueryBase {
    friend class Query;
protected:
    typedef TextQuery::line_no line_no;
    virtual ~QueryBase() {}
private:
    // eval returns the |set| of lines that this Query matches
    virtual set<line_no> eval(const TextQuery&) const = 0;

    // display prints the query
    virtual ostream& display(ostream& = cout) const = 0;
};


class WordQuery: public QueryBase {
    // Query uses the WordQuery constructor
    friend class Query;

    WordQuery(const string& s): query_word(s) {}

    // concrete class: WordQuery defines all inherited pure virtual functions

    set<line_no> eval(const TextQuery& tq) const {
        return tq.run_query(query_word);
    }

    ostream& display(ostream& os) const {
        return os << query_word;
    }

    string query_word;
};


// handle class to manage the Query_base inheritance hierarchy
class Query {
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator~(const Query&);
public:
    // builds a new WordQuery
    Query(const string& s): q(new WordQuery(s)), use(new size_t(1)) {}

    // copy control to manage pointers and use counting

    Query(const Query& other): q(other.q), use(other.use) {
        ++*use;
    }

    ~Query() { decr_use(); }

    Query& operator=(const Query& rhs) {
        ++*rhs.use;
        decr_use();
        q = rhs.q;
        use = rhs.use;
        return *this;
    }

    // interface functions: will call corresponding QueryBase operations

    set<TextQuery::line_no> eval(const TextQuery& tq) const {
        return q->eval(tq);
    }

    ostream& display(ostream& os) const {
        return q->display(os);
    }

private:
    Query(QueryBase* query): q(query), use(new size_t(1)) {}

    void decr_use() {
        if (--*use == 0) {
            delete q;
            delete use;
        }
    }

    QueryBase * q;
    size_t * use;
};

inline ostream&
operator<<(ostream& os, const Query& q) {
    return q.display(os);
}


class NotQuery: public QueryBase {
    friend Query operator~(const Query&);

    NotQuery(Query q): query(q) {}

    // concrete class: NotQuery defines all inherited pure virtual functions

    set<line_no> eval(const TextQuery&) const;

    ostream& display(ostream& os) const {
        return os << "~(" << query << ")";
    }

    const Query query;
};


class BinaryQuery: public QueryBase {
protected:
    BinaryQuery(Query left, Query right, const string& op):
        lhs(left), rhs(right), oper(op) {}

    // abstract class: BinaryQuery doesn't define eval

    ostream& display(ostream& os) const {
        return os << "(" << lhs << " " << oper << " " << rhs << ")";
    }

    const Query lhs, rhs;  // right- and left-hand operands
    const string oper;  // name of the operator
};


class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

    AndQuery(Query left, Query right): BinaryQuery(left, right, "&") {}

    // concrete class: AndQuery inherits display and defines 
    // remaining pure virtual

    set<line_no> eval(const TextQuery&) const;
};


class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

    OrQuery(Query left, Query right): BinaryQuery(left, right, "|") {}

    // concrete class: OrQuery inherits display and defines 
    // remaining pure virtual

    set<line_no> eval(const TextQuery&) const;
};


inline Query operator&(const Query& lhs, const Query& rhs) {
    return new AndQuery(lhs, rhs);
}

inline Query operator|(const Query& lhs, const Query& rhs) {
    return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query& oper) {
    return new NotQuery(oper);
}


// returns intersection of its operands' result sets
set<TextQuery::line_no> AndQuery::eval(const TextQuery& tq) const {
    // virtual calls through the Query handle to get result sets
    // for the operands
    set<line_no> left = lhs.eval(tq), right = rhs.eval(tq);
    
    set<line_no> ret_lines;  // destination to hold results
    
    // writes intersection of two ranges to a destination iterator
    // destination iterator in this call adds elements to ret
    set_intersection(left.begin(), left.end(),
        right.begin(), right.end(), inserter(ret_lines, ret_lines.begin()));

    return ret_lines;
}

// returns union of its operands' result sets
set<TextQuery::line_no> OrQuery::eval(const TextQuery& tq) const {
    // virtual calls through the Query handle to get result sets
    // for the operands
    set<line_no> right = rhs.eval(tq);    
    set<line_no> ret_lines = lhs.eval(tq);  // destination to hold results
    
    // inserts the lines from right that aren't already in ret_lines
    ret_lines.insert(right.begin(), right.end());

    return ret_lines;
}

// returns lines not in its operand's result set
set<TextQuery::line_no> NotQuery::eval(const TextQuery& tq) const {
    // virtual call through the Query handle to eval
    set<line_no> has_val = query.eval(tq);
    set<line_no> ret_lines;
    // for each line in the input file, check whether that line is in has_val
    // if not, add that line number to ret_lines
    for (line_no i=0; i<tq.size(); ++i) {
        if (has_val.find(i) == has_val.end()) {
            ret_lines.insert(i);
        }
    }

    return ret_lines;
}

#endif