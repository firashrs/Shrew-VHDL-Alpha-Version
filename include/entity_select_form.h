#ifndef ENTITY_SELECT_FORM_H
#define ENTITY_SELECT_FORM_H

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/msgdlg.h>
#include <wx/gdicmn.h>
#include "ui_drawer.h"
#include "color_palette.h"



class entity_select_form : public wxFrame {
    public:
        int selected_entity = -1;
        std::vector<std::string> entity_list;
        entity_select_form(std::vector<std::string> all_entities, wxSize* panel_position, wxSize* panel_size) ;
    //    {
    //        idList = idListCtrl;
    //        entity_list = all_entities;
    //        buttonDialog->Bind(wxEVT_BUTTON, [&](wxCommandEvent& e) {
    //            std::cout<<"FUUUUCK NEW 22 "<<std::endl;
    //
    //            int selection_count = listCtrl->GetSelectedItemCount();
    //            if (selection_count != 1) {
    //
    //                wxMessageBox("You have to select one entity!", _("Error !"));
    //            } else {
    //                std::string text =  (std::string)listCtrl->GetItemText(selected_entity);
    //                this->Hide();
    ////                parent->chosen_entity(text);
    //
    //            }
    //        });
    //
    //        listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, [&](wxListEvent& event) {
    //            /*UserInputDialog dialog(this);
    //            dialog.SetInputText(inputText->GetLabel());
    //            if (dialog.ShowModal() == wxID_OK) inputText->SetLabel(dialog.GetInputText());*/
    //
    //
    //            int id =  (int)event.GetItem();
    //            selected_entity = id;
    //        });
    //
    //        listCtrl->AppendColumn("Entities", wxLIST_FORMAT_LEFT, 80);
    //        for (int i = 0; i < entity_list.size(); i++) {
    //
    //            listCtrl->InsertItem(i, entity_list[i]);
    //        }
    //        /*listCtrl->InsertItem(0, "Second");
    //        listCtrl->InsertItem(1, "First");*/
    //    }
    private:
        wxListCtrl* listCtrl;


    //wxStaticText* inputText = new wxStaticText(panel, wxID_ANY, "User input text", {10, 50});
};

#endif // ENTITY_SELECT_FORM_H
