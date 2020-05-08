#include<iostream>
#include<string>
#include<vector>

enum class Color{Red,Yellow,Blue};
enum class Size{small,Medium,Large};

struct  Product{
	std::string name;
	Color color;
	Size size;
};


//OLD ! Open for modification !!
struct ProductFilter{

	typedef std::vector<Product*> Items;

	static Items by_color(Items items,Color color){
		Items result;
		for(auto& e:items)
			if(e->color == color)
				result.push_back(e);
		return result;
	}

	static Items by_size(Items items,Size size){
		Items result;
		for(auto& e:items)
			if(e->size == size)
				result.push_back(e);
		return result;
	}

	static Items by_color_and_size(Items items,Color color,Size size){
		Items result;
		for(auto& e:items)
			if(e->color == color && e->size == size)
				result.push_back(e);
		return result;
	}
};

//NEW : Open for extension and closed for modification

template <typename T> struct ISpecification{

	virtual bool is_satisfied(T *item) = 0;

};

template <typename T> struct IFilter{

	virtual std::vector<T*> filter (std::vector<T*> items,ISpecification<T>& spec) = 0;

};

struct BetterFilter : IFilter<Product>{

    typedef std::vector<Product*> Items;

    std::vector<Product*> filter (std::vector<Product*> items,ISpecification<Product>& spec){
        Items result;
        for(auto& e:items)
            if(spec.is_satisfied(e))
                result.push_back(e);
        return result;
    }
};

struct ColorSpecification: ISpecification<Product> {

    Color color;

    explicit ColorSpecification(const Color color):color{color}{}

    bool is_satisfied(Product * item) override {
        return item->color == color ;
    }
};

struct SizeSpecification: ISpecification<Product> {

    Size size;

    explicit SizeSpecification(const Size size):size{size}{}

    bool is_satisfied(Product * item) override {
        return item->size == size ;
    }
};

template<typename T> struct AndSpecification : ISpecification<T> {

    ISpecification<T>& first;
    ISpecification<T>& second;

    AndSpecification(ISpecification<T>& first,ISpecification<T>& second):first{first}, second{second} {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main(){

    Product Apple{"Apple",Color::Yellow,Size::small};
    Product Tree{"Tree",Color::Blue,Size::Large};
    Product House{"House",Color::Yellow,Size::Large};

    std::vector<Product*> all{&Apple,&Tree,&House};

    BetterFilter bf;
    ColorSpecification yellow(Color::Yellow);

    auto yellow_thing = bf.filter(all,yellow);

    for(auto& e:yellow_thing)
        std::cout << e->name << " is Yellow" << std::endl;

    SizeSpecification big(Size::Large);
    AndSpecification<Product> yellow_and_large{yellow,big};

    auto yellow_large_thing = bf.filter(all,yellow_and_large);
    for(auto&e :yellow_large_thing)
        std::cout << e->name << " is Yellow and Large" << std::endl;

    return 0;
}
