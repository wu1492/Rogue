#include <iostream>
#include <string>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include "DungeonXMLHandler.hpp"
#include <exception>
#include <atomic> 
#include <sstream>
#include "ObjectDisplayGrid.hpp"
#include "GridChar.hpp"
#include "KeyboardListener.hpp"
#include <vector> 
#include <thread>
#include <mutex>

std::atomic_bool isRunning(true);


void displayDungeon(ObjectDisplayGrid* grid, Dungeon* dungeon, int *x, int *y,int* room_num){
        int topHeight = dungeon->topHeight;
        int height = dungeon->bottomHeight + dungeon->topHeight + dungeon->gameHeight;
        for(int i = 0;i < dungeon->width;i++){
            for(int j = 0; j < height;j++){
                grid->addObjectToDisplay(new GridChar(' '),i,j);
            }
        }
        
        dungeon->item_stack_list.resize(dungeon->width);
        for(int i = 0;i<dungeon->width;i++){
            dungeon->item_stack_list[i].resize(height);
        }
        for(int i = 0; i < dungeon->num_rooms;i++){
            int posleft = dungeon->rooms[i]->posX;
            int posright = posleft + dungeon->rooms[i]->width-1;
            int postop = dungeon->rooms[i]->posY + topHeight;
            int posbottom = postop + dungeon->rooms[i]->height-1;
            

            for(int k = postop +1; k < posbottom;k++){
                
                for(int j = posleft + 1; j < posright;j++){
                    grid->addObjectToDisplay(new GridChar('.'),j,k);
                }
            }
            for(int k = 0; k<dungeon->rooms[i]->creature_size;k++){
                grid->addObjectToDisplay(new GridChar(dungeon->rooms[i]->creatures[k]->type),dungeon->rooms[i]->creatures[k]->posX+posleft,dungeon->rooms[i]->creatures[k]->posY+postop);
                dungeon->addCreature(dungeon->rooms[i]->creatures[k]);
                dungeon->creatures.back()->posX = dungeon->rooms[i]->creatures[k]->posX+posleft;
                dungeon->creatures.back()->posY = dungeon->rooms[i]->creatures[k]->posY+postop;
                //std::cout << dungeon->rooms[i]->creatures[k]->type;
            }
            for(int k = 0; k<dungeon->rooms[i]->item_size;k++){
                grid->addObjectToDisplay(new GridChar(dungeon->rooms[i]->items[k]->type),dungeon->rooms[i]->items[k]->posX+posleft,dungeon->rooms[i]->items[k]->posY+postop);
                dungeon->item_stack_list[dungeon->rooms[i]->items[k]->posX+posleft][dungeon->rooms[i]->items[k]->posY+postop].push_back(dungeon->rooms[i]->items[k]);
            }
            if(i == (dungeon->player->room-1)){
                grid->addObjectToDisplay(new GridChar('@'),dungeon->player->posX+posleft,dungeon->player->posY+postop);
                *x = dungeon->player->posX+posleft;
                *y = dungeon->player->posY+postop;
                dungeon->player->posX = *x;
                dungeon->player->posY = *y;
            }
            for(int l = postop; l <= posbottom;l++){
                grid->addObjectToDisplay(new GridChar('X'),posright,l);
                grid->addObjectToDisplay(new GridChar('X'),posleft,l);
            }
            for(int l = posleft; l <= posright;l++){
                grid->addObjectToDisplay(new GridChar('X'),l,postop);
                grid->addObjectToDisplay(new GridChar('X'),l,posbottom);
            }
            
        }
        for(int l = 0; l < dungeon->num_passages;l++){
            for(int m = 0; m < dungeon->passages[l]->num_posx - 1;m++){
                    
                if(dungeon->passages[l]->posxs[m] == dungeon->passages[l]->posxs[m+1]){
                    int x = dungeon->passages[l]->posxs[m];
                    int min = dungeon->passages[l]->posys[m];
                    int max = dungeon->passages[l]->posys[m+1];
                    if(min > max){
                        int temp = min;
                        min = max;
                        max = temp;
                    }
                    for(int k = min; k <= max;k++){
                            if(grid->getchar(x,k+topHeight) == 'X'){ 
                                grid->addObjectToDisplay(new GridChar('+'),x,k+topHeight);
                            }
                            else{
                                grid->addObjectToDisplay(new GridChar('#'),x,k+topHeight);
                            }
                    }
                }
                else{
                    int y = dungeon->passages[l]->posys[m];
                    int min = dungeon->passages[l]->posxs[m];
                    int max = dungeon->passages[l]->posxs[m+1];
                    if(min > max){
                        int temp = min;
                        min = max;
                        max = temp;
                    }
                    for(int k = min; k <= max;k++){
                            if(grid->getchar(k,y+topHeight) == 'X'){ 
                                grid->addObjectToDisplay(new GridChar('+'),k,y+topHeight);
                            }
                            else{
                                grid->addObjectToDisplay(new GridChar('#'),k,y+topHeight);
                            }
                    }
                }
            }
        }
        grid -> update();
}

int main(int argc, char* argv[]) {
    Dungeon* dungeon;
    std::string fileName;
    try{
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n";
        std::cout << "Exception message is: \n"
             << message << "\n";
        xercesc::XMLString::release(&message);
        return 1;
    }
    switch (argc) {
        case 2:
            fileName = "./xmlfiles/" + ((std::string) argv[1]);
            break;
        default:
            std::cout << "C++ Test <xmlfilename>" << std::endl;
    }
    xercesc::SAX2XMLReader* parser = xercesc::XMLReaderFactory::createXMLReader();

    try {
        DungeonXMLHandler* handler = new DungeonXMLHandler();
        parser->setContentHandler(handler);
        parser->setErrorHandler(handler);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
        XMLCh * fileNameXMLEnc = xercesc::XMLString::transcode(fileName.c_str()); //Encode string as UTF-16, but transcode needs casting as const char * (not std::string)
        parser->parse(fileNameXMLEnc);
        xercesc::XMLString::release(&fileNameXMLEnc);
        dungeon = handler->getDungeon();
        //dungeon.toString();
		delete parser;
		delete handler;
        /*
         * the above is a different form of 
         for (int i = 0; i < students.length; i++) {
            std::cout << students[i] << std::endl;
        }
        */
    } catch (const xercesc::XMLException& toCatch) {
            char* message = xercesc::XMLString::transcode(toCatch.getMessage());
            std::cout << "Exception message is: \n"
                 << message << "\n";
            xercesc::XMLString::release(&message);
            return -1;
    }
    catch (const xercesc::SAXParseException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        xercesc::XMLString::release(&message);
        return -1;
    }
	catch(std::exception& e){
	    std::cout << e.what() << '\n';
	}
	catch(...){
        std::cout << "Unexpected Exception \n" ;
        return -1;
	}
    
    xercesc::XMLPlatformUtils::Terminate(); //valgrind will say there's memory errors if not included
	
    ObjectDisplayGrid grid(dungeon->width,dungeon->topHeight,dungeon->gameHeight,dungeon->bottomHeight,5);
    ObjectDisplayGrid* pGrid = &grid;
    int x = -1;
    int y = -1;
    int room_num = -1;    // The room pkayer is in
    int creature_num = -1;  // the index of the player in its room

    int height = dungeon->topHeight + dungeon->gameHeight;
    
    displayDungeon(pGrid,dungeon,&x,&y,&room_num);

    KeyboardListener listener(pGrid);
    listener.run(&x,&y,dungeon);
    
    return 0;
}



