#include <iostream>
#include "folder.h"
#include "message.h"

using namespace std;

Folder::Folder():
name("NonNameFolder") {

}

Folder::Folder(const string& name_):
name(name_) {

}

Folder::~Folder() {
    while (!messages.empty()) {
        (*messages.begin())->remove(*this);
    }
}

void Folder::add_msg(Message * msg) {
    messages.insert(msg);
}

void Folder::rm_msg(Message * msg) {
    messages.erase(msg);
}

ostream& Folder::display_msgs(ostream& out) {
    out << "================Messages in " << name << "=================" << "\n";
    int i = 1;
    for (set<Message*>::const_iterator it=messages.begin();
    it!=messages.end(); ++it, ++i) {
        out << " No." << i << " ";
        (*it)->display(out);
    }
    out << "=======================================================" << "\n";

    return out;
}