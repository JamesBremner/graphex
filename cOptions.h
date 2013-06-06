namespace graphex {

	using namespace System::ComponentModel;

/**

  Enumerate the layout options

*/
	public enum class eLayout {
		//[Description("Move vertices by dragging with mouse")]
		Manual,
		//[Description("Auomatically place vertices in a circle")]
		Circle,
		Spring,
	};

/**

  Convert layout options from/to strings

*/
public ref class MyEnumConverter : public EnumConverter
{
public:
	MyEnumConverter() : EnumConverter( eLayout::typeid ) {}
};

/**

  The graphex options

*/
public ref class cOptions
{
public:
		eLayout^ myLayout;
public:

	cOptions()
		: myLayout(eLayout::Circle)
	{}

	[Category("Configuration")]
	[Description("Location of vertices")]
	[TypeConverter(MyEnumConverter::typeid)]
	property eLayout^ Layout
	{
		eLayout^ get() { return myLayout; }
		void set( eLayout^ value ) { myLayout = value; }
	}

};

}