class Landmark
{
    public:
        Landmark (string name) : m_name(name){};
        virtual ~Landmark(){};
        virtual string color() const;
        virtual string icon() const = 0; 
        string name() const;
    private:
        string m_name;
};

string Landmark::color() const{
    return "yellow";
}

string Landmark::name() const{
    return m_name;
}

class Hotel : public Landmark
{
    public:
        Hotel(string name);
        ~Hotel() {cout << "Destorying the hotel " << name() << "." << endl;}
        virtual string icon() const;
};

string Hotel::icon() const
{
    return "bed"; 
}

Hotel::Hotel(string name): Landmark(name)
{
}

class Restaurant : public Landmark
{
    public:
        Restaurant(string name, int capacity): Landmark(name), m_capacity(capacity) {};
        ~Restaurant() {cout << "Destorying the restaurant " << name() << "." << endl;}
        virtual string icon() const;
    private:
        int m_capacity;
};

string Restaurant::icon() const
{
    if(m_capacity < 40)
        return "small knife/fork";
    else
        return "large knife/fork";
}

class Hospital : public Landmark
{
    public:
        Hospital(string name) : Landmark(name) {};
        ~Hospital() {cout << "Destorying the hospital " << name() << "." << endl;}
        virtual string icon() const;
        virtual string color() const;
};

string Hospital::icon() const 
{
    return "H";
}

string Hospital::color() const
{
    return "blue";
}

void display(const Landmark* lm)
{
    cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
	 << lm->name() << "." << endl;
}