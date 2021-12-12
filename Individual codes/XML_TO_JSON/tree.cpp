#include "tree.hpp"

Tree::Tree(){
    
}


// ********************************  Helper Function**********************************
string Tree::ind(int depth)
{
    string indent;
    for(int i = 0; i < depth; i++)
        indent += "   ";
    return indent;
}



tag Tree::get_tag_struct(string s1, string name)
{
    tag t;
    string s = "<" + s1 + " " + name;
    string tmp = "";
    for(size_t i = 1;; i++)
    {
        if(s[i] == ' ' || i == s.length() - 1)
        {
            t.name = tmp;
            break;
        }
        else
        {
            tmp += s[i];
        }
    }
    int sp = -1, eq = -1;

    while(1)
    {
        if(sp == -1)
            sp = s.find(' ', sp + 1) - 1;
        else
            sp = s.find("\" ", sp + 1);
        eq = s.find('=', eq + 1);
        if(sp == string::npos)
            return t;
        pair<string, string> p;
        p.first = s.substr(sp + 2, eq - 1 - sp);
        p.second = s.substr(eq + 1, s.find('\"', eq + 2) - eq);
        t.attr.push_back(p);
    }
}


void Tree::print_attr(vector<pair<string, string>> s, int depth)
{
    for(size_t i = 0; i < s.size(); i++)
    {
        if(i)
        {
            cout << ",\n";
        }
        cout << ind(depth) << "\"@" << s[i].first << "\": " << s[i].second;
    }
}

void Tree::get_same_tag(Node* r, int ind, vector<int>& index)
{
    index = {};
    index.push_back(ind);
    for(size_t i = ind + 1; i < r->children.size(); i++)
    {
        if(r->children[i]->name == r->children[ind]->name)
        {
            index.push_back(i);
            r->children[i]->found = true;
        }
    }
}
// ******************************************************************


// ********************************  Build Tree **********************************
void Tree::parse_and_bulid_xml_tree(const std::string& xml)
{
    // initialization
    std::string content;
    std::string tagName;
    std::string attributes;
    Node* curr_node = nullptr;
    this->root = new Node("");
    Node* curr_root = this->root;

    for(size_t i = 0; i < xml.size(); i++)
    {
        // starting of a tag
        if(xml[i] == '<')
        {
            // checking version tag and ignore it
            if(xml[i + 1] == '?' || xml[i + 1] == '!')
            {
                // get end of the tag
                i = xml.find('>', i);
            }
            // checking Opening Tag
            else if(xml[i + 1] != '/')
            {
                // skip '<' charachter
                i++;
                tagName = "";
                // ignore spacing in the begining of tag name
                i = xml.find_first_not_of(' ', i);
                // get tag name
                while(xml[i] != ' ' && xml[i] != '>')
                    tagName += xml[i++];
                // make a new node and add it to this root
                curr_node = curr_root->addChild(tagName);
                curr_root = curr_node;
                // get attributes of the tag
                attributes = "";
                while(xml[i] != '>')
                    attributes += xml[i++];
                curr_node->attributes = attributes;
                // skip '>' charachter
                i++;
                // ignore the spacing of indentation
                while(xml[i] == ' ' || xml[i] == '\n' || xml[i] == '\t')
                    i++;
                // checking for nasted tag or not
                if(xml[i] == '<')
                {
                    i--;
                    continue;
                }
                else
                {
                    // get content of that tag
                    content = "";
                    while(xml[i] != '<')
                    {
                        // multi lines content
                        if(xml[i] == '\n')
                        {
                            // skip '\n' charachter
                            i++;
                            // ignore the spacing of indentation
                            i = xml.find_first_not_of(' ', i);
                        }
                        content += xml[i++];
                    }
                    curr_node->value = content;
                    i--;
                }
            }
            // it is a closing Tag
            else
            {
                curr_root = curr_root->parent;
                // skip content of the closing tag
                i = xml.find('>', i);
            }
        }
        // if not a starting of a tag then ignore it
    }
    root = root->children[0];
}
// ******************************************************************


// ********************************  XML formater **********************************
void Tree::_print_xml(Node* root, int level)
{
    cout << ind(level) << "<" << root->name << root->attributes << ">\n";

    if(root->value != "")
        cout << ind(level) << "  " << root->value << std::endl;

    for(size_t i = 0; i < root->children.size(); i++)
    {
        _print_xml(root->children[i], level + 1);
    }

    cout << ind(level) << "</" << root->name << ">\n";
}


void Tree::print_xml()
{
    _print_xml(this->root, 0);
}
// ******************************************************************



// ********************************  Minifing **********************************
void Tree::_minifing(Node* root)
{
    cout <<"<" << root->name << root->attributes << ">"<< root->value;
    for(size_t i = 0; i < root->children.size(); i++)
    {
        _minifing(root->children[i]);
    }

    cout << "</" << root->name << ">";
}


void Tree::minifing()
{
    _minifing(root);
}

// ******************************************************************



// ********************************  JSON **********************************
void Tree::_print_json(Node* r, bool flag = true)
{
    static int depth = 1;
    tag t = get_tag_struct(r->name, r->attributes);
    if(r->children.size() == 0)
    {
        if(flag)
        {
            cout << ind(depth) << "\"" << t.name << "\": ";
        }
        if(t.attr[0].first != "")
        {
            if(!flag)
                cout << ind(depth) << "{" << endl;
            depth++;
            print_attr(t.attr, depth);
            cout << ",\n";
            if(r->value != "")
            {
                cout << ind(depth) << "\"#text"
                     << ": " << '"' << r->value << "\"\n";
            }
            depth--;
            cout << ind(depth) << "}";
        }
        else
        {
            cout << '"' << r->value << '"';
        }
        return;
    }
    else
    {
        vector<int> index;
        if(r->children.size() > 1)
        {
            if(flag)
            {
                cout << ind(depth) << '"' << t.name << "\": {\n";
                depth++;
            }
            if(t.attr[0].first != "")
            {
                print_attr(t.attr, depth);
                cout << ",\n";
            }
            for(size_t i = 0; i < r->children.size(); i++)
            {
                if(r->children[i]->found)
                {
                    continue;
                }
                if(i)
                {
                    cout << ",\n";
                }
                get_same_tag(r, i, index);
                if(index.size() > 1)
                {
                    Node* ch = r->children[i];

                    cout << ind(depth) << "\"" << ch->name << "\": [\n";
                    depth++;

                    if(ch->children.size() == 0 && ch->attributes == "")
                    {
                        for(size_t x = 0; x < index.size(); x++)
                        {
                            if(x)
                            {
                                cout << ",\n";
                            }

                            cout << ind(depth) << "\"" << r->children[index[x]]->value << "\"";
                        }
                    }
                    else
                    {
                        for(size_t x = 0; x < index.size(); x++)
                        {
                            if(x)
                            {
                                cout << ",\n";
                            }
                            if(r->children[index[x]]->children.size())
                            {

                                cout << ind(depth) << "{\n";
                                depth++;
                                _print_json(r->children[index[x]], false);
                                depth--;
                                cout << "\n";

                                cout << ind(depth) << "}";
                            }
                            else
                            {
                                _print_json(r->children[index[x]], false);
                            }
                        }
                    }
                    depth--;
                    cout << "\n";

                    cout << ind(depth) << "]";
                }
                else
                {
                    _print_json(r->children[i]);
                }
            }
            if(flag)
            {
                depth--;
                cout << "\n";

                cout << ind(depth) << "}";
            }
        }
        else
        {
            cout << ind(depth) << '"' << t.name << '"' << ": {\n";
            depth++;
            if(t.attr[0].first != "")
            {
                print_attr(t.attr, depth);
                cout << ",\n";
            }
            for(size_t i = 0; i < r->children.size(); i++)
            {
                if(i)
                {

                    cout << ind(depth) << ",\n";
                }
                _print_json(r->children[i]);
            }
            depth--;
            cout << "\n";

            cout << ind(depth) << "}";
        }
    }
}


void Tree::print_json(){
    cout << '{' << endl;
    _print_json(this->root,true);
    cout << "\n}\n";
}


string Tree::convert_to_json()
{
    /*
     * set the buffer of cout to json_file string stream
     * used to extract the output form cout
     * cout and json_file stream will be connected
     */
    streambuf* backup;
    backup = cout.rdbuf(); // back up cout's streambuf
    stringstream json_file;
    cout.rdbuf(json_file.rdbuf());
    
    
    // print JSON in json_file stream
    print_json();

    // rest cout buffer stream
    cout.rdbuf(backup);

    return json_file.str();
}

// ******************************************************************

Tree::~Tree()
{
    delete root;
}
