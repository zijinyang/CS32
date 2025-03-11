void listAll(string path, const Class* c)  // two-parameter overload
{
    if (c != nullptr)
    {
        if(path == "")
            path += c->name();
        else{
            path += "=>";
            path += c->name();
        }

        for (int k = 0; k < c->subclasses().size(); k++){
            listAll(path, c->subclasses()[k]);
        }
        cout << path << endl;
    }
}