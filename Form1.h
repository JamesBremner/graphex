#pragma once

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


#include "cOptions.h"
#include "cGraph.h"


namespace graphex {



			 enum display_enum {
				 none,
				 graph,
				 options,

			 } ;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
			: flagVertexDragging( false )
			, flagfilling( false )
		{
			theOptions = gcnew cOptions();
			InitializeComponent();
			GraphPropertyGrid->SelectedObject = theOptions;
			//theGraph.setOptions( theOptions );
			String^ n = theOptions->myDBFilepath;
			theGraph.OpenDB(  msclr::interop::marshal_as<std::wstring>( n ));
		} 

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

			display_enum  myCurDisplay;
			cOptions^ theOptions;
			bool flagVertexDragging;
			bool flagfilling;






	private: System::Windows::Forms::DataGridView^  VertexGridView;
	private: System::Windows::Forms::DataGridView^  EdgeGridView;
	private: System::Windows::Forms::DataGridView^  MatrixGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Name;
	private: System::Windows::Forms::Panel^  graphpanel;
	private: System::Windows::Forms::PropertyGrid^  GraphPropertyGrid;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FixedX;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FixedY;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  vertexToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  edgeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  graphToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dInteractiveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  graphMLToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  readToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  writeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->VertexGridView = (gcnew System::Windows::Forms::DataGridView());
			this->Name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FixedX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FixedY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EdgeGridView = (gcnew System::Windows::Forms::DataGridView());
			this->MatrixGridView = (gcnew System::Windows::Forms::DataGridView());
			this->graphpanel = (gcnew System::Windows::Forms::Panel());
			this->GraphPropertyGrid = (gcnew System::Windows::Forms::PropertyGrid());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->vertexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->edgeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->graphToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dInteractiveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->graphMLToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->readToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->writeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->VertexGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->EdgeGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MatrixGridView))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// VertexGridView
			// 
			this->VertexGridView->AllowUserToOrderColumns = true;
			this->VertexGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->VertexGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->Name, 
				this->FixedX, this->FixedY});
			this->VertexGridView->Location = System::Drawing::Point(166, 27);
			this->VertexGridView->Name = L"VertexGridView";
			this->VertexGridView->RowHeadersWidth = 30;
			this->VertexGridView->Size = System::Drawing::Size(151, 150);
			this->VertexGridView->TabIndex = 5;
			this->VertexGridView->UserAddedRow += gcnew System::Windows::Forms::DataGridViewRowEventHandler(this, &Form1::VertexGridView_UserAddedRow);
			this->VertexGridView->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::VertexGridView_CellEndEdit);
			this->VertexGridView->RowsRemoved += gcnew System::Windows::Forms::DataGridViewRowsRemovedEventHandler(this, &Form1::VertexGridView_RowsRemoved);
			// 
			// Name
			// 
			this->Name->HeaderText = L"Name";
			this->Name->Name = L"Name";
			// 
			// FixedX
			// 
			this->FixedX->HeaderText = L"FixedX";
			this->FixedX->Name = L"FixedX";
			// 
			// FixedY
			// 
			this->FixedY->HeaderText = L"FixedY";
			this->FixedY->Name = L"FixedY";
			// 
			// EdgeGridView
			// 
			this->EdgeGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->EdgeGridView->Location = System::Drawing::Point(352, 27);
			this->EdgeGridView->Name = L"EdgeGridView";
			this->EdgeGridView->Size = System::Drawing::Size(140, 150);
			this->EdgeGridView->TabIndex = 6;
			// 
			// MatrixGridView
			// 
			this->MatrixGridView->AllowUserToAddRows = false;
			this->MatrixGridView->AllowUserToDeleteRows = false;
			this->MatrixGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->MatrixGridView->Location = System::Drawing::Point(523, 27);
			this->MatrixGridView->Name = L"MatrixGridView";
			this->MatrixGridView->RowHeadersWidth = 100;
			this->MatrixGridView->Size = System::Drawing::Size(128, 150);
			this->MatrixGridView->TabIndex = 7;
			this->MatrixGridView->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::MatrixGridView_CellEndEdit);
			// 
			// graphpanel
			// 
			this->graphpanel->Location = System::Drawing::Point(671, 27);
			this->graphpanel->Name = L"graphpanel";
			this->graphpanel->Size = System::Drawing::Size(149, 150);
			this->graphpanel->TabIndex = 8;
			this->graphpanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::graphpanel_Paint);
			this->graphpanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::graphpanel_MouseMove);
			this->graphpanel->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::graphpanel_MouseClick);
			this->graphpanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::graphpanel_MouseDown);
			this->graphpanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::graphpanel_MouseUp);
			// 
			// GraphPropertyGrid
			// 
			this->GraphPropertyGrid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->GraphPropertyGrid->Location = System::Drawing::Point(166, 192);
			this->GraphPropertyGrid->Name = L"GraphPropertyGrid";
			this->GraphPropertyGrid->Size = System::Drawing::Size(130, 130);
			this->GraphPropertyGrid->TabIndex = 9;
			this->GraphPropertyGrid->PropertyValueChanged += gcnew System::Windows::Forms::PropertyValueChangedEventHandler(this, &Form1::GraphPropertyGrid_PropertyValueChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->vertexToolStripMenuItem, 
				this->edgeToolStripMenuItem, this->graphToolStripMenuItem, this->optionToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(859, 24);
			this->menuStrip1->TabIndex = 10;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// vertexToolStripMenuItem
			// 
			this->vertexToolStripMenuItem->Name = L"vertexToolStripMenuItem";
			this->vertexToolStripMenuItem->Size = System::Drawing::Size(51, 20);
			this->vertexToolStripMenuItem->Text = L"Vertex";
			this->vertexToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::vertexToolStripMenuItem_Click);
			// 
			// edgeToolStripMenuItem
			// 
			this->edgeToolStripMenuItem->Name = L"edgeToolStripMenuItem";
			this->edgeToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->edgeToolStripMenuItem->Text = L"Edge";
			this->edgeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::edgeToolStripMenuItem_Click);
			// 
			// graphToolStripMenuItem
			// 
			this->graphToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->newToolStripMenuItem, 
				this->dInteractiveToolStripMenuItem, this->graphMLToolStripMenuItem});
			this->graphToolStripMenuItem->Name = L"graphToolStripMenuItem";
			this->graphToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->graphToolStripMenuItem->Text = L"Graph";
			// 
			// dInteractiveToolStripMenuItem
			// 
			this->dInteractiveToolStripMenuItem->Name = L"dInteractiveToolStripMenuItem";
			this->dInteractiveToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->dInteractiveToolStripMenuItem->Text = L"2D Interactive";
			this->dInteractiveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::dInteractiveToolStripMenuItem_Click);
			// 
			// graphMLToolStripMenuItem
			// 
			this->graphMLToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->readToolStripMenuItem, 
				this->writeToolStripMenuItem});
			this->graphMLToolStripMenuItem->Name = L"graphMLToolStripMenuItem";
			this->graphMLToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->graphMLToolStripMenuItem->Text = L"GraphML";
			// 
			// readToolStripMenuItem
			// 
			this->readToolStripMenuItem->Name = L"readToolStripMenuItem";
			this->readToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->readToolStripMenuItem->Text = L"Read";
			this->readToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::readToolStripMenuItem_Click);
			// 
			// writeToolStripMenuItem
			// 
			this->writeToolStripMenuItem->Name = L"writeToolStripMenuItem";
			this->writeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->writeToolStripMenuItem->Text = L"Write";
			this->writeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::writeToolStripMenuItem_Click);
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(51, 20);
			this->optionToolStripMenuItem->Text = L"Option";
			this->optionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::optionToolStripMenuItem_Click);
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::newToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(859, 567);
			this->Controls->Add(this->GraphPropertyGrid);
			this->Controls->Add(this->graphpanel);
			this->Controls->Add(this->MatrixGridView);
			this->Controls->Add(this->EdgeGridView);
			this->Controls->Add(this->VertexGridView);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Text = L"Raven\'s Point Graph Explorer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->VertexGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->EdgeGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MatrixGridView))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		 void HideAll()
		 {
			 myCurDisplay = none;
			VertexGridView->Hide();
			EdgeGridView->Hide();
			MatrixGridView->Hide();
			graphpanel->Hide();
			GraphPropertyGrid->Hide();
		 }

		/**

		User want Vertices

		*/

private: System::Void btnVertices_Click(System::Object^  sender, System::EventArgs^  e) {
			 HideAll();
			 VertexGridView->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 VertexGridView->Location = System::Drawing::Point(130, 15);
			 VertexGridView->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

			 flagfilling = true;

			 if( theGraph.getVertexCount() < 1 ) {
				 VertexGridView->Rows->Clear();
				 flagfilling = false;
				 return;
			 }

			VertexGridView->RowCount = theGraph.getVertexCount()+1;
			for( int kv = 0; kv < theGraph.getVertexCount(); kv++ )
			{
				VertexGridView->Rows[kv]->Cells[0]->Value =
					gcnew String( theGraph.getNameVertex( kv ).c_str() );
				if( theGraph.IsPinned(kv) ) {
					double x,y;
					theGraph.getVertexLocation( x, y, kv );
					VertexGridView->Rows[kv]->Cells[1]->Value = x;
					VertexGridView->Rows[kv]->Cells[2]->Value = y;
				} else {
					// vertex is not pinned
					VertexGridView->Rows[kv]->Cells[1]->Value = nullptr;
					VertexGridView->Rows[kv]->Cells[2]->Value = nullptr;
				}
			}

			flagfilling = false;

		 }
		 /**

		 User want matrix

		 */
private: System::Void btnMatrix_Click(System::Object^  sender, System::EventArgs^  e) {
			  HideAll();
			 MatrixGridView->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 MatrixGridView->Location = System::Drawing::Point(130, 15);
			 MatrixGridView->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

			 // Add row and column for each vertex
			MatrixGridView->RowCount = theGraph.getVertexCount();
			MatrixGridView->ColumnCount = theGraph.getVertexCount();
			for( int kv = 0; kv < theGraph.getVertexCount(); kv++ )
			{
				MatrixGridView->Columns[kv]->HeaderText = gcnew String( theGraph.getNameVertex( kv ).c_str() );
				MatrixGridView->Rows[kv]->HeaderCell->Value = gcnew String( theGraph.getNameVertex( kv ).c_str() );

				for( int kc = kv; kc <  theGraph.getVertexCount(); kc++ ) {
					MatrixGridView->Rows[kv]->Cells[kc]->Style->BackColor = Color::Wheat;
				}

				MatrixGridView->Columns[kv]->Width = 50;
	
			}


			int a,b;
			for( int ke = 0; ke < theGraph.getEdgeCount(); ke++ ) {
				theGraph.getEdge( a, b, ke );
				MatrixGridView->Rows[a]->Cells[b]->Value = L"1";
			}

		 }


		 /**

		 User wants to see the graph layout

		 */
private: System::Void btnLayout_Click(System::Object^  sender, System::EventArgs^  e) {

			 // display the graph panel
			 HideAll();
			 myCurDisplay = graph;
			 graphpanel->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 graphpanel->Location = System::Drawing::Point(130, 15);
			 graphpanel->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

			 if( ! theGraph.IsPlanar() ) {
				 Graphics^ g = graphpanel->CreateGraphics();
				 g->DrawString(
					 L"ERROR: Graph is not Planar",
					 gcnew System::Drawing::Font( "Arial",16 ),
					 gcnew SolidBrush( Color::Red ),
					 25,25 );
				 delete g;
				 return;
			 }
			 // update the layout
			 switch( *(theOptions->myLayout) ) {
				 case eLayout::Manual:
				 default:
					 break;
				 case eLayout::Circle:
					 theGraph.ArrangeCircle();
					 break;
				 case eLayout::Spring:
					 theGraph.ArrangeKK();
					 break;
			 }

			 theGraph.MapColor();


			 // redraw it
			 graphpanel->Invalidate();
		 }

private: System::Void btnOptions_Click(System::Object^  sender, System::EventArgs^  e) {
			 HideAll();
			 myCurDisplay = options;
			 GraphPropertyGrid->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 GraphPropertyGrid->Location = System::Drawing::Point(130, 15);
			 GraphPropertyGrid->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );
		 }

private: System::Void MatrixGridView_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {

			 if( e->RowIndex == e->ColumnIndex ) {
				 // Cell edited was on the leading diagonal
				 // It is meaningless to connect a vertex to itself
				 // So just ignore this
				 return;
			 }

			 if( MatrixGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value == nullptr ) {
				 // The edited cell contains nothing
				 // Delete any relationship
				 theGraph.RemoveEdge( e->RowIndex,e->ColumnIndex );
				 return;
			 }

			 // Add the relationship
			 theGraph.AddEdge(
				 e->RowIndex,e->ColumnIndex,
				 msclr::interop::marshal_as<std::wstring>( 
				 MatrixGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString() ) );

		 }
private: System::Void VertexGridView_UserAddedRow(System::Object^  sender, System::Windows::Forms::DataGridViewRowEventArgs^  e) {

			 theGraph.AddVertex();
		 }
		 /**

		 User has completed editing a vertex grid cell

		 */
private: System::Void VertexGridView_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
		 {

			 if( e->ColumnIndex == 0 ) {
				 // vertex name
				 if( VertexGridView->Rows[e->RowIndex]->Cells[0]->Value == nullptr ) {
					 VertexGridView->Rows[e->RowIndex]->Cells[0]->Value = "___Deleted";
				 }
				 int error = theGraph.setNameVertex(
					 e->RowIndex,
					  msclr::interop::marshal_as<std::wstring>(
						VertexGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString() ) );
				 if( error ) {
					 // error returned from trying to set the vertex name
					 // probably there is already a vertex with this name
					 // get the previous name, before user attempted to change it
					 String^ old_name = gcnew String( theGraph.getNameVertex( e->RowIndex ).c_str() );
					 if( ! old_name->Length ) {
						 // there was no previous name
						 // assign one that is likely to be unique
						 old_name = L"_new_vertex_" + e->RowIndex.ToString();
						 theGraph.setNameVertex( e->RowIndex,
							  msclr::interop::marshal_as<std::wstring>( old_name ) );
					 }
					 // reset name to unique value
					 VertexGridView->Rows[e->RowIndex]->Cells[0]->Value = old_name;
				 }
			 } else {
				 // fixed location
				 if( VertexGridView->Rows[e->RowIndex]->Cells[1]->Value == nullptr &&
					 VertexGridView->Rows[e->RowIndex]->Cells[2]->Value == nullptr ) {
						 // free location
						 theGraph.setFreeLocation( e->RowIndex );
				 } else {
					 double x, y;
					 if( VertexGridView->Rows[e->RowIndex]->Cells[1]->Value == nullptr ) {
						 x = 0.0;
					 } else {
						 x = Convert::ToDouble(VertexGridView->Rows[e->RowIndex]->Cells[1]->Value);
					 }
					 if( VertexGridView->Rows[e->RowIndex]->Cells[2]->Value == nullptr ) {
						 y = 0.0;
					 } else {
						 y = Convert::ToDouble(VertexGridView->Rows[e->RowIndex]->Cells[2]->Value);
					 }
					 theGraph.setFixedLocation( e->RowIndex, x, y );
				 }
			 }

		 }

		 /**

		 Paint the graph layout panel

		 */
private: System::Void graphpanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

			 if( myCurDisplay != graph ) {
				 return;
			 }

			 // Draw the edges first,
			 // so they end up behind the verices

			 int xo, yo;
			 theGraph.getScreenOrigin( xo, yo );

			 for( int ke = 0; ke < theGraph.getEdgeCount(); ke++ ) {
				 int iva, ivb;
				 theGraph.getEdge( iva, ivb, ke );
				 double xa, ya, xb, yb;
				 theGraph.getVertexLocation( xa, ya, iva );
				 theGraph.getVertexLocation( xb, yb, ivb );
				 e->Graphics->DrawLine( gcnew Pen(Color::Black, 3),
					 (float)xa+xo, (float)ya+yo, (float)xb+xo, (float)yb+yo );
			 }
			 // Draw the vertices
			 for( int kv = 0; kv < theGraph.getVertexCount(); kv++ ) {
				 double xv, yv;
				 cVertex& v = theGraph.getVertex( kv );
				 theGraph.getVertexLocation( xv, yv, kv );
				 // Represent vertex with a box of specified color
				 const int box_size = theGraph.getVertexBoxSize();
				 SolidBrush^ brush = gcnew SolidBrush(Color::Black);
				 switch( v.myColor ) {
		case 0: brush->Color = Color::LightGreen; break;
		case 1: brush->Color = Color::Red; break;
		case 2: brush->Color = Color::Blue; break;
		case 3: brush->Color = Color::Yellow; break;
				 }

				 int x = (int)xv + xo;
				 int y = (int)yv + yo;
				 e->Graphics->FillRectangle( brush,
					 x-box_size/2,y-box_size/2,box_size,box_size);

				 // label the vertex
				 e->Graphics->DrawString(gcnew System::String(v.myName.c_str()), 
					 gcnew System::Drawing::Font( "Arial",16 ),
					 gcnew SolidBrush( Color::Black ),
					 (float)x-box_size/2,(float)y-box_size/2);
			 }

  
			 // Highlight selected vertex
			 cVertex& v = theGraph.getVertexSelected();
			 if( v.myName.length() ) {
				 int x = (int)v.getLocationX()+xo;
				 int y = (int)v.getLocationY()+yo;
				 const int box_size = theGraph.getVertexBoxSize();
				 e->Graphics->DrawRectangle( gcnew Pen( Color::Black,3.0f ),
					x-box_size/2,y-box_size/2,box_size,box_size);
			 }

		 }
private: System::Void VertexGridView_RowsRemoved(System::Object^  sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^  e) {
			 if( flagfilling )
				 return;
			 theGraph.RemoveVertex(e->RowIndex);
		 }
private: System::Void graphpanel_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 }
private: System::Void graphpanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if ( Control::ModifierKeys == Keys::Shift ) {
				 // user has clicked with shift key pressed
				 // If he has selected a second vertex
				 // add edge, or remove if already present
				 int old_selected_index = theGraph.getVertexSelectedIndex();
				 theGraph.MouseClick(e->X,e->Y);
				 if( old_selected_index >= 0 ) {		 
					 int new_selected_index = theGraph.getVertexSelectedIndex();
					 if( new_selected_index >= 0 ) {
						 if( theGraph.IsEdge( old_selected_index, new_selected_index ) ) {
							 theGraph.RemoveEdge(  old_selected_index, new_selected_index );
						 } else {
							theGraph.AddEdge( old_selected_index, new_selected_index, L"" );
						 }
					 }
				 }
			 } else {
				 theGraph.MouseClick(e->X,e->Y);
			 }
			 graphpanel->Invalidate();
			 flagVertexDragging = theGraph.IsSelectedVertex();

		 }
private: System::Void graphpanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if( flagVertexDragging ) {
				 theGraph.SaveSelectedVertexLocationToDB();
			 }
			 flagVertexDragging = false;
		 }
private: System::Void graphpanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if( ! flagVertexDragging )
				 return;
			 theGraph.setLocationSelectedVertex( e->X,e->Y);
			 graphpanel->Invalidate();

			 // switch off auto arrangement of vertex location
			 // so we don't lose the user's new location
			 *(theOptions->myLayout) = eLayout::Manual; 
		 }

private: System::Void GraphPropertyGrid_PropertyValueChanged(System::Object^  s, System::Windows::Forms::PropertyValueChangedEventArgs^  e) {
			 if( e->ChangedItem->Label == "FilePath" ) {
				 theGraph.Clear();
				 String^ n = theOptions->myDBFilepath;
				 theGraph.OpenDB(msclr::interop::marshal_as<std::wstring>( n ));
			 }
		 }
private: System::Void dInteractiveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 // display the graph panel
			 HideAll();
			 myCurDisplay = graph;
			 graphpanel->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 graphpanel->Location = System::Drawing::Point(130, 25);
			 graphpanel->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

			 if( ! theGraph.IsPlanar() ) {
				 Graphics^ g = graphpanel->CreateGraphics();
				 g->DrawString(
					 L"ERROR: Graph is not Planar",
					 gcnew System::Drawing::Font( "Arial",16 ),
					 gcnew SolidBrush( Color::Red ),
					 25,25 );
				 delete g;
				 return;
			 }
			 // update the layout
			 switch( *(theOptions->myLayout) ) {
				 case eLayout::Manual:
				 default:
					 break;
				 case eLayout::Circle:
					 theGraph.ArrangeCircle();
					 break;
				 case eLayout::Spring:
					 theGraph.ArrangeKK();
					 break;
			 }

			 theGraph.MapColor();


			 // redraw it
			 graphpanel->Invalidate();		
		 }

private: System::Void optionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 HideAll();
			 myCurDisplay = options;
			 GraphPropertyGrid->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 GraphPropertyGrid->Location = System::Drawing::Point(130, 25);
			 GraphPropertyGrid->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );
		 }
private: System::Void edgeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  HideAll();
			 MatrixGridView->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 MatrixGridView->Location = System::Drawing::Point(130, 25);
			 MatrixGridView->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

			 // Add row and column for each vertex
			MatrixGridView->RowCount = theGraph.getVertexCount();
			MatrixGridView->ColumnCount = theGraph.getVertexCount();
			for( int kv = 0; kv < theGraph.getVertexCount(); kv++ )
			{
				MatrixGridView->Columns[kv]->HeaderText = gcnew String( theGraph.getNameVertex( kv ).c_str() );
				MatrixGridView->Rows[kv]->HeaderCell->Value = gcnew String( theGraph.getNameVertex( kv ).c_str() );

				for( int kc = kv; kc <  theGraph.getVertexCount(); kc++ ) {
					MatrixGridView->Rows[kv]->Cells[kc]->Style->BackColor = Color::Wheat;
				}

				MatrixGridView->Columns[kv]->Width = 50;
	
			}


			int a,b;
			for( int ke = 0; ke < theGraph.getEdgeCount(); ke++ ) {
				theGraph.getEdge( a, b, ke );
				MatrixGridView->Rows[a]->Cells[b]->Value = L"1";
			}
		 }
private: System::Void vertexToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 HideAll();
			 VertexGridView->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 VertexGridView->Location = System::Drawing::Point(130, 25);
			 VertexGridView->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

			 flagfilling = true;

			 if( theGraph.getVertexCount() < 1 ) {
				 VertexGridView->Rows->Clear();
				 flagfilling = false;
				 return;
			 }

			VertexGridView->RowCount = theGraph.getVertexCount()+1;
			for( int kv = 0; kv < theGraph.getVertexCount(); kv++ )
			{
				VertexGridView->Rows[kv]->Cells[0]->Value =
					gcnew String( theGraph.getNameVertex( kv ).c_str() );
				if( theGraph.IsPinned(kv) ) {
					double x,y;
					theGraph.getVertexLocation( x, y, kv );
					VertexGridView->Rows[kv]->Cells[1]->Value = x;
					VertexGridView->Rows[kv]->Cells[2]->Value = y;
				} else {
					// vertex is not pinned
					VertexGridView->Rows[kv]->Cells[1]->Value = nullptr;
					VertexGridView->Rows[kv]->Cells[2]->Value = nullptr;
				}
			}

			flagfilling = false;
		 }
private: System::Void writeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

			 openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
			 openFileDialog1->FilterIndex = 2;
			 openFileDialog1->CheckFileExists = false;

			 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			 {
				 theGraph.WriteGraphML( msclr::interop::marshal_as<std::wstring>(openFileDialog1->FileName));
			 }
		 }
private: System::Void readToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

			 openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
			 openFileDialog1->FilterIndex = 2;

			 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			 {
				 theGraph.ReadGraphML(msclr::interop::marshal_as<std::wstring>(openFileDialog1->FileName));

			 }
		 }
private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 theGraph.Clear();
			graphpanel->Invalidate();	
		 }
};
}

