#ifndef DUNGEONXMLHANDLER_H_
#define DUNGEONXMLHANDLER_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Action.hpp"
#include "Armor.hpp"
#include "BlessCurseOwner.hpp"
#include "ChangedDisplayedType.hpp"
#include "Creature.hpp"
#include "CreatureAction.hpp"
#include "Displayable.hpp"
#include "DropPack.hpp"
#include "Dungeon.hpp"
#include "EndGame.hpp"
#include "Hallucinate.hpp"
#include "Item.hpp"
#include "ItemAction.hpp"
#include "Monster.hpp"
#include "ObjectDisplayGrid.hpp"
#include "Passage.hpp"
#include "Player.hpp"
#include "Remove.hpp"
#include "Room.hpp"
#include "Scroll.hpp"
#include "Structure.hpp"
#include "Sword.hpp"
#include "Teleport.hpp"
#include "UpdateDisplay.hpp"
#include "YouWin.hpp"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>

class DungeonXMLHandler : public xercesc::DefaultHandler{
private:
    int DEBUG = 1;
    std::string CLASSID = "DungeonXMLHandler";
    std::string data ;
    Dungeon* dungeon;
    Room* roombeingparsed; 
    Item* itembeingparsed;
    ItemAction* itemactionbeingparsed;
    Creature* creabeingparsed; // creature being parsed
    CreatureAction* creaactionbeingparsed;
    Player* playerbeingparsed;
    Monster* monsterbeingparsed;
    Passage* passagebeingparsed;
    
    bool bactionmsg = false; // action message
    bool bactionint = false; // action int value
    bool bactionchar = false; // action char value
    
    bool bitemint = false; // item int value

    bool bvisible = false;
    bool bposx = false;
    bool bposy = false;
    bool bhp = false;
    bool bhpmoves = false;
    bool bmaxhit = false;
    bool bheight = false;
    bool bwidth = false;
    bool btype = false;
    

    bool is_room = false; // check the master of each variable
    bool is_crea = false; // creature
    bool is_item = false;
    bool is_pass = false;

    bool is_item_action = false;
    bool is_crea_action = false;
public:
    Dungeon* getDungeon();
    DungeonXMLHandler();
    void startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes) ;
    void endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName) ;
    void fatalError(const xercesc::SAXParseException&);
    void characters(const XMLCh * const ch, const XMLSize_t length ) ;
    //std::string toString();


};

#endif /* STUDENTXMLHANDLER_H_ */
