    while(node != nullptr){
                        int slot = hash(node->key);
                        if(table[slot] != nullptr){
                            node->next = table[slot];                        
                        }
                        table[slot] = node;
                        node = node->next;
                