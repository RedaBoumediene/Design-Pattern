#include<iostream>

class Rectangle{

    protected:
        int width , height;

    public:
        Rectangle(const int w, const int h):width{w},height{h}{}
        virtual int Getwidth() const {
            return width;
        }
        virtual int GetHeight() const {
            return height;
        }
        virtual void SetWidth(const int w){
            this->width = w;
        }
        virtual void SetHeight(const int h){
            this->height = h;
        }
        int Area() const {
            return width*height;
        }
};

class Square : public Rectangle {

    public:
        Square(int sz):Rectangle(sz,sz){}
        void SetWidth(const int w) override {
            width = height = w;
        }
        void SetHeight(const int v) override {
            width = height = v;
        }
};

//The violation of Liskov substitution

void process(Rectangle& r){
    int w = r.Getwidth();
    r.SetHeight(10);
    std::cout << "Expect area is " << (w*10) << " , got " << r.Area() << std::endl;
}

//Better to creat another instead to inherit from Rectangle

struct RectangleFactory {
    static Rectangle CreateRectangle(int w,int h);
    static Rectangle CreateSquare(int sz);
};

int main(){

    Rectangle r(2,8);
    process(r);

    Square s(5);
    process(s);

    return 0;
}
