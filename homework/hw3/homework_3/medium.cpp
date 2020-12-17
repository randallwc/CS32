//What you'll turn in for this problem will be a file named medium.cpp containing the definitions and implementations of the four classes, and nothing more.

class Medium
{
private:
    string m_id;
public:
    Medium(string id): m_id(id){};
    string id() const { return m_id; };
    
    virtual string connect() const = 0;
    virtual string transmit(string msg) const  = 0;
    virtual ~Medium() {};
};

class TwitterAccount : public Medium
{
public:
    TwitterAccount(string acctName) : Medium(acctName) {};
    virtual string connect() const { return "Tweet"; };
    virtual string transmit(string msg) const
    {
        return "text: " + msg;
    };
    virtual ~TwitterAccount()
    {
        cout << "Destroying the Twitter account " + id() + "." << endl;
    }
};

class Phone : public Medium
{
private:
    CallType m_callType;
public:
    Phone(string number, CallType callType) : Medium(number), m_callType(callType) {};
    virtual string connect() const { return "Call"; };
    virtual string transmit(string msg) const
    {
        if(m_callType == 0)
        {
            msg = "voice: " + msg;
        }
        else
        {
            msg = "text: " + msg;
        }
        return msg;
    };
    virtual ~Phone()
    {
        cout << "Destroying the phone " + id() + "." << endl;
    }
};

class EmailAccount : public Medium
{
public:
    EmailAccount(string email) : Medium(email) {};
    virtual string connect() const { return "Email"; };
    virtual string transmit(string msg) const
    {
        return "text: " + msg;
    };
    virtual ~EmailAccount()
    {
        cout << "Destroying the email account " + id() + "." << endl;
    }
};

