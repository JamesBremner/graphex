#pragma once
using namespace System;
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
		System::String^ myDBFilepath;
public:

	cOptions()
		: myLayout(eLayout::Circle)
//		, myDBFilepath( gcnew String(L"C:/ProgramData/ravenspoint/graphex.dat"))
		, myDBFilepath( gcnew String(L"graphex.dat"))
	{}

	[Category("Configuration")]
	[Description("Location of vertices")]
	[TypeConverter(MyEnumConverter::typeid)]
	property eLayout^ Layout
	{
		eLayout^ get() { return myLayout; }
		void set( eLayout^ value ) { myLayout = value; }
	}

	[Category("Configuration")]
	[Description("Path to file storing project database")]
	[Editor(System::Windows::Forms::Design::FileNameEditor::typeid,
		System::Drawing::Design::UITypeEditor::typeid)]
    property String^ FilePath
	{
		String^ get() { return myDBFilepath; }
		void set( String^ value ) { myDBFilepath = value; }
	}

};

}