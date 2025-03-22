 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function ifillArray() public returns (bool){
        if(listAddresses.length<1500) {
             
            for(uint i=0;i<350;i++) {
                listAddresses.push(msg.sender);
            }
            return true;

        } else {
            listAddresses = new address[](0);
            return false;
        }
    }
}
