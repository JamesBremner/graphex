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
			theGraph.setOptions( theOptions );
			theGraph.OpenDB();
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

	private: System::Windows::Forms::Button^  btnVertices;
	private: System::Windows::Forms::Button^  btnMatrix;
	private: System::Windows::Forms::Button^  btnEdges;
	private: System::Windows::Forms::Button^  btnLayout;
	private: System::Windows::Forms::Button^  btnOptions;
	private: System::Windows::Forms::DataGridView^  VertexGridView;
	private: System::Windows::Forms::DataGridView^  EdgeGridView;
	private: System::Windows::Forms::DataGridView^  MatrixGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Name;
	private: System::Windows::Forms::Panel^  graphpanel;
	private: System::Windows::Forms::PropertyGrid^  GraphPropertyGrid;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FixedX;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FixedY;


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
			this->btnVertices = (gcnew System::Windows::Forms::Button());
			this->btnMatrix = (gcnew System::Windows::Forms::Button());
			this->btnEdges = (gcnew System::Windows::Forms::Button());
			this->btnLayout = (gcnew System::Windows::Forms::Button());
			this->btnOptions = (gcnew System::Windows::Forms::Button());
			this->VertexGridView = (gcnew System::Windows::Forms::DataGridView());
			this->Name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FixedX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FixedY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EdgeGridView = (gcnew System::Windows::Forms::DataGridView());
			this->MatrixGridView = (gcnew System::Windows::Forms::DataGridView());
			this->graphpanel = (gcnew System::Windows::Forms::Panel());
			this->GraphPropertyGrid = (gcnew System::Windows::Forms::PropertyGrid());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->VertexGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->EdgeGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MatrixGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// btnVertices
			// 
			this->btnVertices->Location = System::Drawing::Point(13, 13);
			this->btnVertices->Name = L"btnVertices";
			this->btnVertices->Size = System::Drawing::Size(75, 57);
			this->btnVertices->TabIndex = 0;
			this->btnVertices->Text = L"Vertices";
			this->btnVertices->UseVisualStyleBackColor = true;
			this->btnVertices->Click += gcnew System::EventHandler(this, &Form1::btnVertices_Click);
			// 
			// btnMatrix
			// 
			this->btnMatrix->Location = System::Drawing::Point(12, 139);
			this->btnMatrix->Name = L"btnMatrix";
			this->btnMatrix->Size = System::Drawing::Size(75, 57);
			this->btnMatrix->TabIndex = 1;
			this->btnMatrix->Text = L"Matrix";
			this->btnMatrix->UseVisualStyleBackColor = true;
			this->btnMatrix->Click += gcnew System::EventHandler(this, &Form1::btnMatrix_Click);
			// 
			// btnEdges
			// 
			this->btnEdges->Location = System::Drawing::Point(13, 76);
			this->btnEdges->Name = L"btnEdges";
			this->btnEdges->Size = System::Drawing::Size(75, 57);
			this->btnEdges->TabIndex = 2;
			this->btnEdges->Text = L"Edges";
			this->btnEdges->UseVisualStyleBackColor = true;
			// 
			// btnLayout
			// 
			this->btnLayout->Location = System::Drawing::Point(12, 202);
			this->btnLayout->Name = L"btnLayout";
			this->btnLayout->Size = System::Drawing::Size(75, 57);
			this->btnLayout->TabIndex = 3;
			this->btnLayout->Text = L"Graph";
			this->btnLayout->UseVisualStyleBackColor = true;
			this->btnLayout->Click += gcnew System::EventHandler(this, &Form1::btnLayout_Click);
			// 
			// btnOptions
			// 
			this->btnOptions->Location = System::Drawing::Point(12, 265);
			this->btnOptions->Name = L"btnOptions";
			this->btnOptions->Size = System::Drawing::Size(75, 57);
			this->btnOptions->TabIndex = 4;
			this->btnOptions->Text = L"Options";
			this->btnOptions->UseVisualStyleBackColor = true;
			this->btnOptions->Click += gcnew System::EventHandler(this, &Form1::btnOptions_Click);
			// 
			// VertexGridView
			// 
			this->VertexGridView->AllowUserToOrderColumns = true;
			this->VertexGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->VertexGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->Name, 
				this->FixedX, this->FixedY});
			this->VertexGridView->Location = System::Drawing::Point(166, 13);
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
			this->EdgeGridView->Location = System::Drawing::Point(353, 13);
			this->EdgeGridView->Name = L"EdgeGridView";
			this->EdgeGridView->Size = System::Drawing::Size(140, 150);
			this->EdgeGridView->TabIndex = 6;
			// 
			// MatrixGridView
			// 
			this->MatrixGridView->AllowUserToAddRows = false;
			this->MatrixGridView->AllowUserToDeleteRows = false;
			this->MatrixGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->MatrixGridView->Location = System::Drawing::Point(518, 13);
			this->MatrixGridView->Name = L"MatrixGridView";
			this->MatrixGridView->RowHeadersWidth = 100;
			this->MatrixGridView->Size = System::Drawing::Size(128, 150);
			this->MatrixGridView->TabIndex = 7;
			this->MatrixGridView->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::MatrixGridView_CellEndEdit);
			// 
			// graphpanel
			// 
			this->graphpanel->Location = System::Drawing::Point(672, 13);
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
			this->Controls->Add(this->btnOptions);
			this->Controls->Add(this->btnLayout);
			this->Controls->Add(this->btnEdges);
			this->Controls->Add(this->btnMatrix);
			this->Controls->Add(this->btnVertices);
			this->Text = L"Raven\'s Point Graph Explorer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->VertexGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->EdgeGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MatrixGridView))->EndInit();
			this->ResumeLayout(false);

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

			 // display the graph panel
			 HideAll();
			 myCurDisplay = graph;
			 graphpanel->Show();
			 System::Drawing::Rectangle r = this->ClientRectangle;
			 graphpanel->Location = System::Drawing::Point(130, 15);
			 graphpanel->Size = System::Drawing::Size(r.Width - 150, r.Height - 50 );

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
					 VertexGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString() );
				 if( error ) {
					 // error returned from trying to set the vertex name
					 // probably there is already a vertex with this name
					 // get the previous name, before user attempted to change it
					 String^ old_name = gcnew String( theGraph.getNameVertex( e->RowIndex ).c_str() );
					 if( ! old_name->Length ) {
						 // there was no previous name
						 // assign one that is likely to be unique
						 old_name = L"_new_vertex_" + e->RowIndex.ToString();
						 theGraph.setNameVertex( e->RowIndex, old_name );
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
			 theGraph.DrawLayout( e->Graphics );

		 }
private: System::Void VertexGridView_RowsRemoved(System::Object^  sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^  e) {
			 if( flagfilling )
				 return;
			 theGraph.RemoveVertex(e->RowIndex);
		 }
private: System::Void graphpanel_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 }
private: System::Void graphpanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 theGraph.MouseClick(e->X,e->Y);
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
				 theGraph.OpenDB();
			 }
		 }
};
}

