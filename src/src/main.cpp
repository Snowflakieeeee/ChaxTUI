// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <memory> // for shared_ptr, __shared_ptr_access
#include <string> // for operator+, to_string
#include <ftxui/component/mouse.hpp>
#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp"                 // for separator, gauge, text, Element, operator|, vbox, border
#include <unordered_map>
#include <iostream>
#include "ftxui/component/event.hpp"
#include "ftxui/screen/string.hpp"

// clang-format off
class Hub
{
public:
    std::vector<std::string> messages;
    std::string name;
    // std::vector<Client> clients;         // list of clients, we'll add this later. This will contain stuff like
                                            // username, status, any other meta data.
    int number_of_clients;
    int serverID;
};

class HubList
{
public:
    std::unordered_map<int, Hub> joined_servers;
    int total_servers;
    // int selected_serverID;
};
// clang-format on

int main()
{
    Hub TwT;
    TwT.name = "Tech With Tim";
    TwT.number_of_clients = 289; // To show member list
    // TwT.messages = ServerObject.get_messages(server_id);   // not sure if this is how you will implement the networking interface
    for (int i = 0; i < 30; i++)
    {
        TwT.messages.push_back("  ");
    }
    TwT.messages.push_back("Tim: I AM THE REAL TIM");
    TwT.messages.push_back("Tim: Alex is the best mod fr");
    TwT.messages.push_back("Tim: Try out chax!");

    Hub CCPP_Help;
    CCPP_Help.name = "C/C++ Help";
    CCPP_Help.number_of_clients = 142;
    for (int i = 0; i < 30; i++)
    {
        CCPP_Help.messages.push_back("  ");
    }
    CCPP_Help.messages.push_back("Anonymous: This is a great channel to ask for C++ help!");
    CCPP_Help.messages.push_back("Dyno: :>");
    CCPP_Help.messages.push_back("Squirtle: Try out chax TUI!"); // currently hard coded msgs
    // I hope we can figure out how to integrate this with the network interface
    // and append messages to this accordingly. Idk

    HubList ClientHubList;
    ClientHubList.joined_servers[0] = TwT;
    ClientHubList.joined_servers[1] = CCPP_Help;
    ClientHubList.total_servers = 2;

    std::string tmpmsg;
    int msg_offset = 0;
    std::vector<std::string> joined_servers;
    for (int i = 0; i < ClientHubList.total_servers; i++)
    {
        joined_servers.push_back(ClientHubList.joined_servers[i].name);
    }
    int selected_server = 0;

    ftxui::Component msgInput = ftxui::Input(&tmpmsg, "enter a message...");
    ftxui::Component sendButton = ftxui::Button("  SEND   ", [&]
                                                { ClientHubList.joined_servers[selected_server].messages.push_back(tmpmsg); tmpmsg.clear() ; });
    ftxui::Component scrollUp = ftxui::Button("   UP    ", [&]
                                              { if (msg_offset < ClientHubList.joined_servers[selected_server].messages.size() - 20){msg_offset += 1;} });
    ftxui::Component scrollDown = ftxui::Button("  DOWN  ", [&]
                                                { if (msg_offset > 0){msg_offset -= 1;} });
    ftxui::Component ServerList = ftxui::Dropdown(&joined_servers, &selected_server);

    auto message_sending_components = ftxui::Container::Horizontal({msgInput, sendButton, scrollUp, scrollDown, ServerList});
    message_sending_components |= ftxui::CatchEvent([&](auto event)
                                                    {
        bool ret = (ftxui::Event::Character('\n') == event);
        if (ret){
            ClientHubList.joined_servers[selected_server].messages.push_back(tmpmsg); 
            tmpmsg.clear();
        }
        return ret; });

    message_sending_components |= ftxui::CatchEvent([&](auto event)
                                                    {
        bool ret = (ftxui::Event::ArrowUp== event);
        if (ret){
            if (msg_offset < ClientHubList.joined_servers[selected_server].messages.size() - 20){
                msg_offset += 1;
            }
        }
        return ret; });

    message_sending_components |= ftxui::CatchEvent([&](auto event)
                                                    {
        bool ret = (ftxui::Event::ArrowDown == event);
        if (ret)
        {
            if (msg_offset > 0)
            {
                msg_offset -= 1;
            }
        }
        return ret; });

    // clang-format off
    auto component = ftxui::Renderer(message_sending_components, [&]
                                     {
                                        auto msgs = ClientHubList.joined_servers[selected_server].messages;
                                         std::string a = msgs[msgs.size() - 1 - msg_offset];
                                         std::string b = msgs[msgs.size() - 2 - msg_offset];
                                         std::string c = msgs[msgs.size() - 3 - msg_offset];
                                         std::string d = msgs[msgs.size() - 4 - msg_offset];
                                         std::string e = msgs[msgs.size() - 5 - msg_offset];
                                         std::string f = msgs[msgs.size() - 6 - msg_offset];
                                         std::string g = msgs[msgs.size() - 7 - msg_offset];
                                         std::string h = msgs[msgs.size() - 8 - msg_offset];
                                         std::string i = msgs[msgs.size() - 9 - msg_offset];
                                         std::string j = msgs[msgs.size() - 10 - msg_offset];

                                         std::string k = msgs[msgs.size() - 11 - msg_offset];
                                         std::string l = msgs[msgs.size() - 12 - msg_offset];
                                         std::string m = msgs[msgs.size() - 13 - msg_offset];
                                         std::string n = msgs[msgs.size() - 14 - msg_offset];
                                         std::string o = msgs[msgs.size() - 15 - msg_offset];
                                         std::string p = msgs[msgs.size() - 16 - msg_offset];
                                         std::string q = msgs[msgs.size() - 17 - msg_offset];
                                         std::string r = msgs[msgs.size() - 18 - msg_offset];
                                         std::string s = msgs[msgs.size() - 19 - msg_offset];
                                         std::string t = msgs[msgs.size() - 20 - msg_offset];
                                         // VERY not neat, but ftxui doesnt support \n in their ftxui::text() element
                                         // nor in their ftxui::paragraph() element
                                         
                                        return ftxui::hbox({
                                            ftxui::vbox({
                                                ftxui::text("Server list"),
                                                ServerList->Render(),
                                            }) | ftxui::border,
                                            
                                            
                                            ftxui::vbox({ftxui::text(s) | ftxui::flex,
                                                             ftxui::text(t) | ftxui::flex,

                                                             ftxui::text(r) | ftxui::flex,
                                                             ftxui::text(q) | ftxui::flex,
                                                             ftxui::text(p) | ftxui::flex,
                                                             ftxui::text(o) | ftxui::flex,

                                                             ftxui::text(n) | ftxui::flex,
                                                             ftxui::text(m) | ftxui::flex,
                                                             ftxui::text(l) | ftxui::flex,
                                                             ftxui::text(k) | ftxui::flex,

                                                             ftxui::text(j) | ftxui::flex,
                                                             ftxui::text(h) | ftxui::flex,
                                                             ftxui::text(g) | ftxui::flex,
                                                             ftxui::text(f) | ftxui::flex,

                                                             ftxui::text(e) | ftxui::flex,
                                                             ftxui::text(d) | ftxui::flex,
                                                             ftxui::text(c) | ftxui::flex,
                                                             ftxui::text(b) | ftxui::flex,
                                                             ftxui::text(a) | ftxui::flex,
                                                             ftxui::separator(),
                                                             
                                                             ftxui::hbox({
                                                                 msgInput->Render() | ftxui::flex | ftxui::border,
                                                                 ftxui::separator(),
                                                                 sendButton->Render()| ftxui::border,
                                                                 ftxui::separator(),
                                                                 scrollUp->Render()| ftxui::border,
                                                                 ftxui::separator(),
                                                                 scrollDown->Render()| ftxui::border,
                                                                 ftxui::separator(),
                                                             })
                                                        }
                                                ) | ftxui::flex});
                                     });
    // clang-format on
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    screen.Loop(component);
    return 0;
}
