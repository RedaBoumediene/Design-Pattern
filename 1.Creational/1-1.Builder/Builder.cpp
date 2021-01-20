#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<memory>
using namespace std;

struct HtmlElement{
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent = 2;

    HtmlElement(){}

    HtmlElement(const string& name,const string& text):name{name},text{text}{}

    string str(int indt = 0) const{
        ostringstream oss;
        string i(indent*indt,' ');

        oss<<i<<"<"<<name<<">"<<endl;

        if(text.size()>0)
            oss<<string(indent*(indt+1),' ')<<text<<endl;

        for(const auto& e:elements)
            oss<<e.str(indent+1);

        oss<<i<<"</"<<name<<">"<<endl;

        return oss.str();
    }
};

struct HtmlBuilder{
    HtmlElement root;

    HtmlBuilder(string root_name){
        root.name = root_name;
    }

    void add_child(string child_name,string child_text){
        HtmlElement e{child_name,child_text};
        root.elements.push_back(e);
    }

    string str() const {
        return root.str();
    }
};

void naive_design(){
    // <p>Hello world</p>
    auto text = "Hello World";
    printf("<p>%s</p>\n",text);

    string words[] = {"Hello","World"};
    ostringstream oss;
    oss<< "<ul>\n";
    for(auto w:words)
        oss<<" <li>"<<w<<"</li>\n";
    oss<<"</ul>";
    printf(oss.str().c_str());
}

int main(){

    //naive_design();

    HtmlBuilder builder("ul");
    builder.add_child("li","Hello");
    builder.add_child("li","World");

    cout<<builder.str()<<endl;

    return 0;
}
