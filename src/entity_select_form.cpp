

#include "entity_select_form.h"

entity_select_form::entity_select_form(std::vector<std::string> all_entities, wxSize* panel_position, wxSize* panel_size) :


    wxFrame(nullptr, wxNewId(), "Choose One Entity...", wxPoint(panel_position->GetWidth(), panel_position->GetHeight()),
              wxSize(panel_size->GetWidth(), panel_size->GetHeight()), wxDEFAULT_FRAME_STYLE) {
                  this->SetMinSize(wxSize(panel_size->GetWidth(), panel_size->GetHeight()));
                  this->SetMaxSize(wxSize(panel_size->GetWidth()*3, panel_size->GetHeight()*2));

    wxPanel* panel = new wxPanel(this, wxNewId(), wxPoint(panel_position->GetWidth(), panel_position->GetHeight()),
              wxSize(panel_size->GetWidth(), panel_size->GetHeight()) );
    panel->SetBackgroundColour(color_palette::bg_color);
    wxBoxSizer *vbox_1 = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(panel, wxID_ANY, _("Choose One Entity\n"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEXTFOLDER"));
    title->SetForegroundColour(color_palette::text_color );
                listCtrl = new wxListCtrl(panel, wxNewId(), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER);

                listCtrl->SetBackgroundColour(color_palette::higher_bg_color);
                listCtrl->SetForegroundColour(color_palette::text_color );

               //vbox_1->Add(title, 0);

               // vbox_1->Add(listCtrl, 1);
      //  left_panel->SetSizer(vbox_1);


        wxPanel* bottom_panel = new wxPanel(panel, wxNewId() );
       wxBoxSizer *hbox_1 = new wxBoxSizer(wxHORIZONTAL);
        wxButton* simulate_button = new wxButton(bottom_panel, wxNewId(), "Simulate", wxDefaultPosition, wxDefaultSize);
        wxButton* cancel_button = new wxButton(bottom_panel, wxNewId(), "Cancel", wxDefaultPosition, wxDefaultSize);
        hbox_1->Add(simulate_button);
        hbox_1->Add(cancel_button);
        bottom_panel->SetSizer(hbox_1);
        vbox_1->Add(title, 0);
        vbox_1->Add(listCtrl, 1, wxEXPAND);
        vbox_1->Add(bottom_panel, 0);
   panel->SetSizer( vbox_1 );



    entity_list = all_entities;
    simulate_button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& e) {


        int selection_count = listCtrl->GetSelectedItemCount();
        if (selection_count != 1) {

            wxMessageBox("You have to select one entity!", _("Error !"));
        } else {
            std::string text =  (std::string)listCtrl->GetItemText(selected_entity);
            this->Hide();
            ui_drawer::close_entity_choosing_form(true, text);

        }
    });

    cancel_button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& e) {
        ui_drawer::close_entity_choosing_form(false, "");
    });

    listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, [&](wxListEvent& event) {

        int id =  (int)event.GetItem();
        selected_entity = id;
    });

    listCtrl->AppendColumn("Entities");
    listCtrl->SetColumnWidth(0, panel_size->GetWidth()-10);
    for (int i = 0; i < entity_list.size(); i++) {

        listCtrl->InsertItem(i, entity_list[i]);
    }
}
