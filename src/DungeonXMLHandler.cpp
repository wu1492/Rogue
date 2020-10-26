#include "DungeonXMLHandler.hpp"

//From https://www.tutorialspoint.com/case-insensitive-string-comparison-in-cplusplus
int case_insensitive_match(std::string s1, std::string s2) {
    //convert s1 and s2 into lower case strings
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower); //std overloads tolower, ::tolower is the definition in the global namespace
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1;
    return 0;
}

inline std::string boolToString(bool booleanValue){
    return booleanValue ? "true": "false";
}

Dungeon* DungeonXMLHandler::getDungeon() {
    return dungeon;
}

DungeonXMLHandler::DungeonXMLHandler() {

}


std::string xmlChToString(const XMLCh* xmlChName, int length = -1){
    //Xerces Parses file into XMLCh* string. So use Transcode to allocate a char* buffer
    char * chStarName = xercesc::XMLString::transcode(xmlChName); 
    if(length == -1){
        std::string StrName(chStarName);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
    else{
        std::string StrName(chStarName,0,length);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }

}

const XMLCh* getXMLChAttributeFromString(const xercesc::Attributes& attributes, const char * strGet){
    XMLCh * xmlChGet = xercesc::XMLString::transcode(strGet);
    const XMLCh * xmlChAttr = attributes.getValue(xmlChGet);
    xercesc::XMLString::release((&xmlChGet));
    return xmlChAttr;
}

void DungeonXMLHandler::startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes){

        char * qNameStr = xercesc::XMLString::transcode(qName);
        if (DEBUG > 1) {
            std::cout << CLASSID << ".startElement qName: " << qNameStr << std::endl;
        }
        if (case_insensitive_match(qNameStr,"Dungeon")) {
            int bottomHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"bottomHeight")));
            int gameHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"gameHeight")));
            int topHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"topHeight")));
            int width = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"width"))); 
            std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            dungeon = new Dungeon(name, width, gameHeight, topHeight, bottomHeight);
            dungeon -> getDungeon(name,width,gameHeight);
            //std::cout << "Initialize Dungeon" << std::endl;
            // to be continued
        }
        else if(case_insensitive_match(qNameStr,"Rooms")){
            //std::cout << "set rooms vector to dungeon" << std::endl;
        }
        else if(case_insensitive_match(qNameStr,"Passages")){

        }
        else if (case_insensitive_match(qNameStr,"Room")) {
            int room = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room")));
            Room* room_ptr = new Room(std::to_string(room)); // Implemented
            room_ptr ->setId(room);
            roombeingparsed = room_ptr;
            is_room = true;
            is_item = false;
            is_crea = false;
            is_pass = false;
            dungeon->addRoom(roombeingparsed);
        }else if(case_insensitive_match(qNameStr,"Player")){
            int _serial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));
            int _room = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room"))); 
            std::string _name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            playerbeingparsed = new Player(); // Implemented
            playerbeingparsed -> room = _room;
            playerbeingparsed -> serial = _serial;
            playerbeingparsed -> name = _name;
            playerbeingparsed -> type = '@';
            creabeingparsed = playerbeingparsed;
            roombeingparsed -> setCreature(playerbeingparsed);
            //dungeon->addCreature(*creabeingparsed);
            is_room = false;
            is_item = false;
            is_crea = true;
            is_pass = false;
        }else if(case_insensitive_match(qNameStr,"Monster")){
            int _serial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));
            int _room = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room"))); 
            std::string _name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            monsterbeingparsed = new Monster(); // Implemented
            monsterbeingparsed -> setID(_room,_serial);
            monsterbeingparsed -> setName(_name);
            roombeingparsed -> setCreature(monsterbeingparsed);
            creabeingparsed = monsterbeingparsed;
            //dungeon->addCreature(*creabeingparsed);
            is_room = false;
            is_item = false;
            is_crea = true;
            is_pass = false;
        }else if(case_insensitive_match(qNameStr,"Scroll")){
            int serial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));
            int room = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room"))); 
            std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            Scroll* scroll_ptr = new Scroll(name); // Implemented
            scroll_ptr->setID(room,serial); // Implemented
            scroll_ptr->type = '?';
            if(playerbeingparsed != NULL){
                scroll_ptr -> setOwner(playerbeingparsed);
            }
            else{
                roombeingparsed->setItem(scroll_ptr);
            }
            itembeingparsed = scroll_ptr;
            //dungeon->addItem(*itembeingparsed);
            is_room = false;
            is_item = true;
            is_crea = false;
            is_pass = false;
        }else if(case_insensitive_match(qNameStr,"Armor")){
            int serial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));
            int room = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room"))); 
            std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            Armor* armor_ptr = new Armor(name); // Implemented
            armor_ptr ->setID(room,serial); // Implemented
            armor_ptr->type = ']';
            if(playerbeingparsed != NULL){
                armor_ptr -> setOwner(playerbeingparsed);
                playerbeingparsed -> setArmor(*armor_ptr);
            }
            else{
                roombeingparsed->setItem(armor_ptr);
            }
            itembeingparsed = armor_ptr;
            //dungeon->addItem(*itembeingparsed);
            is_room = false;
            is_item = true;
            is_crea = false;
            is_pass = false;
        }else if(case_insensitive_match(qNameStr,"Sword")){
            int serial = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"serial")));
            int room = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room"))); 
            std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            Sword* sword_ptr = new Sword(name); // Implemented
            sword_ptr->setID(room,serial); // Implemented
            sword_ptr->type = ')';
            if(playerbeingparsed != NULL){
                sword_ptr -> setOwner(playerbeingparsed);
                playerbeingparsed->setWeapon(*sword_ptr);
            }
            else{
                roombeingparsed->setItem(sword_ptr);
            }
            itembeingparsed = sword_ptr;
            //dungeon->addItem(*itembeingparsed);
            is_room = false;
            is_item = true;
            is_crea = false;
            is_pass = false;
        }else if(case_insensitive_match(qNameStr,"ItemAction")){
            std::string type = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
            std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            if(name.compare("Hallucinate") == 0){
                itemactionbeingparsed = new Hallucinate(itembeingparsed); // Need to be Implement, not sure if owner of item action is item or creature
            }
            else if(name.compare("BlessArmor")==0){
                itemactionbeingparsed = new BlessCurseOwner(itembeingparsed); // Need to be Implement
            }
            is_item_action = true;
            is_crea_action = false;
        }else if(case_insensitive_match(qNameStr,"CreatureAction")){
            std::string type = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
            std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            
            if(name.compare("Teleport") == 0){
                creaactionbeingparsed = new Teleport(name,creabeingparsed); // Need to be implement
            }
            else if(name.compare("DropPack")==0){
                creaactionbeingparsed = new DropPack(name,creabeingparsed); // Need to be implement
            }
            else if(name.compare("EndGame")==0){
                creaactionbeingparsed = new EndGame(name,creabeingparsed); // Need to be implement
            }
            else if(name.compare("ChangeDisplayedType")==0){
                creaactionbeingparsed = new ChangedDisplayedType(name,creabeingparsed); // Need to be implement
            }
            else if(name.compare("Remove")==0){
                creaactionbeingparsed = new Remove(name,creabeingparsed); // Need to be implement
            }
            else if(name.compare("YouWin")==0){
                creaactionbeingparsed = new YouWin(name,creabeingparsed); // Need to be implement
            }
            else if(name.compare("UpdateDisplay")==0){
                creaactionbeingparsed = new UpdateDisplay(name,creabeingparsed); // Need to be implement
            }

            if(type.compare("death")==0){
                creabeingparsed->setDeathAction(creaactionbeingparsed);
            }
            if(type.compare("hits")==0){
                creabeingparsed->setHitAction(creaactionbeingparsed);
            }
            is_item_action = false;
            is_crea_action = true;
        }else if(case_insensitive_match(qNameStr,"Passage")){
            int room2 = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room2")));
            int room1 = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room1")));
            passagebeingparsed = new Passage();
            dungeon->addPassage(passagebeingparsed);
            passagebeingparsed -> setID(room1,room2);
            passagebeingparsed -> setName(std::to_string(room1) + " " + std::to_string(room2));
            is_room = false;
            is_item = false;
            is_crea = false;
            is_pass = true;
        } else if (case_insensitive_match(qNameStr,"posX")) {
            bposx = true;
        } else if (case_insensitive_match(qNameStr,"posY")) {
            bposy = true;
        } else if (case_insensitive_match(qNameStr,"visible")) {
            bvisible = true;
        } else if (case_insensitive_match(qNameStr,"hp")) {
            bhp = true;
        } else if (case_insensitive_match(qNameStr,"hpMoves")) {
            bhpmoves = true;
        } else if (case_insensitive_match(qNameStr,"maxhit")) {
            bmaxhit = true;
        } else if (case_insensitive_match(qNameStr,"height")) {
            bheight = true;
        } else if (case_insensitive_match(qNameStr,"width")) {
            bwidth = true;
        } else if (case_insensitive_match(qNameStr,"type")) {
            btype = true;
        } else if (case_insensitive_match(qNameStr,"ItemIntValue")) {   
            bitemint = true; 
        } else if (case_insensitive_match(qNameStr,"actionMessage")) {
            bactionmsg = true;
        } else if (case_insensitive_match(qNameStr,"actionIntValue")) {
            bactionint = true;
        } else if (case_insensitive_match(qNameStr,"actionCharValue")) {
            bactionchar = true;
        } else {
            std::cout <<"Unknown qname: " << qNameStr << std::endl;
        }
        xercesc::XMLString::release(&qNameStr);
}

void DungeonXMLHandler::endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName)  {
        
        Displayable* target = NULL;
        if(is_crea){
            target = creabeingparsed;
        }
        else if(is_room){
            target = roombeingparsed;
        }
        else if(is_item){
            target = itembeingparsed;
            if(bitemint){
                target ->setIntValue(std::stoi(data));
                bitemint = false;
            }
        }
        else if(is_pass){
            target = passagebeingparsed;
        }

        if (bvisible) {
            if(std::stoi(data) == 1){
                target -> setVisible();
            }
            else{
                target -> setInvisible();
            }
            bvisible = false;
        } else if (bposx) {
            target -> setPosX(std::stoi(data));
            bposx = false;
        } else if (bposy) {
            target -> setPosY(std::stoi(data));
            bposy = false;
        } else if (bhp) {
            target -> setHp(std::stoi(data));
            bhp = false;
        } else if (bhpmoves) {
            target -> setHpMove(std::stoi(data));
            bhpmoves = false;
        } else if (bmaxhit) {
            target -> setMaxHit(std::stoi(data));
            bmaxhit = false;
        } else if (bheight) {
            target -> setHeight(std::stoi(data));
            bheight = false;
        } else if (bwidth) {
            target -> setWidth(std::stoi(data));
            bwidth = false;
        } else if (btype) {
            target -> setType(data[0]);
            btype = false;
        } 

        Action* action_target = NULL;
        if(is_crea_action){
            action_target = creaactionbeingparsed;
        }
        else if(is_item_action){
            action_target = itemactionbeingparsed;
            if(bitemint){
                action_target ->setIntValue(std::stoi(data));
                bitemint = false;
            }
        }

        if(bactionchar){
            action_target -> setCharValue(data[0]);
            bactionchar = false;
        }
        else if(bactionint){
            action_target -> setIntValue(std::stoi(data));
            bactionint = false;
        }
        else if(bactionmsg){
            action_target -> setMessage(data);
            bactionmsg = false;
        }

        char *  qNameStr = xercesc::XMLString::transcode(qName);
        if (case_insensitive_match(qNameStr,"Room")) {
            roombeingparsed = NULL;
        } else if (case_insensitive_match(qNameStr,"Item")) {
            itemactionbeingparsed = NULL;
        } else if (case_insensitive_match(qNameStr,"ItemAction")) {
            itemactionbeingparsed = NULL;
        } else if (case_insensitive_match(qNameStr,"Creature")) {
            creabeingparsed = NULL;
        } else if (case_insensitive_match(qNameStr,"CreatureAction")) {
            creaactionbeingparsed = NULL;
        } else if (case_insensitive_match(qNameStr,"Player")) {
            playerbeingparsed = NULL;
        } else if (case_insensitive_match(qNameStr,"Monster")) {
            monsterbeingparsed = NULL;
        }

        xercesc::XMLString::release(&qNameStr);

}

/*void StudentXMLHandler::addStudent(Student student) {
    students[studentCount++] = student;
}*/

void DungeonXMLHandler::characters(const XMLCh * const ch, const XMLSize_t length) {
        data = xmlChToString(ch,(int)length) ;   
        if (DEBUG > 1) {
			std::cout << CLASSID + ".characters: " << data << std::endl;
            std::cout.flush();
        }
}

void DungeonXMLHandler::fatalError(const xercesc::SAXParseException& exception)
{
    char* message = xercesc::XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << std::endl;
    xercesc::XMLString::release(&message);
}

/*std::string DungeonXMLHandler::toString() {
    std::string str = "StudentsXMLHandler\n";
    str += "   maxStudents: " + std::to_string(maxStudents) + "\n";
    str += "   studentCount: " + std::to_string(studentCount) + "\n";
    for (Student student : students) {
        str += student.toString() + "\n";
    }
    str += "   studentBeingParsed: " + studentBeingParsed->toString() + "\n";
    str += "   activityBeingParsed: " + activityBeingParsed->toString() + "\n";
    str += "   bInstructor: " + boolToString(bInstructor)  + "\n";
    str += "   bCredit: " + boolToString(bCredit) + "\n";
    str += "   bName: " + boolToString(bName) + "\n";
    str += "   bNumber: " + boolToString(bNumber) + "\n";
    str += "   bLocation: " + boolToString(bLocation) + "\n";
    str += "   bMeetingTime: " + boolToString(bMeetingTime) + "\n";
    str += "   bMeetingDay: " + boolToString(bMeetingDay) + "\n";
    return str;
}*/
