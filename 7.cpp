#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>
using namespace std;

class UIElement
{
public:
    string Name;
};

class FrameworkElement: public UIElement
{
public:
    double Width;
    double Height;
    double OffsetLeft;
    double OffsetTop;
    int GridCol = 1;
    int GridRow = 1;
    virtual void UpdateLayout() {}
};

class Panel: public FrameworkElement
{
public:
    void Add(FrameworkElement* child);
    FrameworkElement* Find(string name);
protected:
    vector<FrameworkElement*> Children;
};

class Grid: public Panel
{
public:
    vector<int> Cols{1};
    vector<int> Rows{1};
    void UpdateLayout();
};

class Shapes: public FrameworkElement {};

class Rectangle: public Shapes
{
public:
    string Fill;
};

Grid root;
vector<Rectangle*> rv;

void Panel::Add(FrameworkElement* child)
{
    Children.push_back(child);
}

FrameworkElement* Panel::Find(string name)
{
    for(int i = 0; i < Children.size(); i++)
    {
        if((Children[i]->Name) == name)
            return Children[i];
        else
        {
            Grid *gpt = dynamic_cast<Grid*>(Children[i]);
            FrameworkElement* nf = 0;
            if(gpt != 0)
                nf = (gpt -> Find(name));

            if(nf == 0)
                continue;
            else
                return nf;
        }
    }

    return nullptr;
}

void Grid::UpdateLayout()
{
    for(int i = 0; i < Children.size(); i++)
    {
        auto pt = Children[i];

        int csum = 0, rsum = 0;
        double w, h;

        for(int i = 0; i < Cols.size(); i++)
            csum += Cols[i];

        for(int i = 0; i < Rows.size(); i++)
            rsum += Rows[i];

        w = Width/csum;
        h = Height/rsum;

        pt->Width = w * Cols[pt->GridCol - 1];
        pt->Height = h * Rows[pt->GridRow - 1];
        pt->OffsetLeft = OffsetLeft;
        for(int i = 0; i < (pt->GridCol) - 1; i++)
            (pt->OffsetLeft) += w * Cols[i];
        pt->OffsetTop = OffsetTop;
        for(int i = 0; i < (pt->GridRow) - 1; i++)
            (pt->OffsetTop) += h * Rows[i];

        Grid* gpt = dynamic_cast<Grid*>(pt);

        if(gpt != 0)
            pt->UpdateLayout();
    }

}

string parent(FrameworkElement*);

int main()
{
    root.Width = 100;
    root.Height = 100;
    root.OffsetLeft = 0;
    root.OffsetTop = 0;

    int num;

    cin >> num;

    for(int i = 0; i < num; i++)
    {
        string type;
        cin >> type;
        Grid* ng = new Grid;
        Rectangle * nr = new Rectangle;
        string command;
        bool f(false);
        bool rf(false);

        while(true)
        {
            if(!f)
            {
                cin >> command;
            }

            if(type == "Grid")
            {
                if(i == 0)
                    ng = &root;

                if(command == "Name")
                {
                    string n;
                    cin >> n;
                    ng->Name = n;
                }
                else if(command == "Cols" || command == "Rows")
                {
                    int c;
                    vector<int> v;
                    
                    cin >> c;

                    for(int j = 0; j < c; j++)
                    {
                        int n;
                        cin >> n;
                        v.push_back(n);
                    }

                    if(command == "Cols")
                        (ng->Cols) = v;
                    else if(command == "Rows")
                        (ng->Rows) = v;
                }
                else if(command == "Parent")
                {
                    command = parent(ng);
                    f = true;
                    continue;
                }
            }
            else if(type == "Rectangle")
            {
                if(!rf)
                    rv.push_back(nr);
                rf = true;

                if(command == "Name")
                {
                    string n;
                    cin >> n;
                    nr -> Name = n;
                }
                if(command == "Fill")
                {
                    string fs;
                    cin >> fs;
                    nr->Fill = fs;
                }
                else if(command == "Parent")
                {
                    command = parent(nr);
                    f = true;
                    continue;
                }
            }
        
        if(command == "end")
            break;

        f = false;
        }
    }

    root.UpdateLayout();

    cout.precision(2);
    for(int i = 0; i < rv.size(); i++)
        cout << rv[i]->Name << " " << rv[i]->Fill << " " <<fixed<<rv[i]->OffsetLeft << " " << rv[i]->OffsetTop << " " << rv[i]->Width << " " <<rv[i]->Height << endl;
    return 0; 
}


string parent(FrameworkElement* f)
{
    string pn;
    int col, row;
    cin >> pn;
    Grid * pt;
    if(pn == root.Name)
        pt = &root;
    else
        pt = dynamic_cast<Grid*>(root.Find(pn));
    pt->Add(f);
    string c;
    while(true)
    {
        cin >> c;

        if(c == "Col")
        {   
            cin >> col;
            f->GridCol = col;
        }
        else if(c == "Row")
        {
            cin >> row;
            f->GridRow = row;
        }
        else
        {
            break;
        }
    }
    return c;
}
