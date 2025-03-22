 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;

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

contract ENS_Permissions {

    address owner;

    constructor(address _owner) {
        owner = _owner;
    }
}

contract Factory {
    function createPermissionsBot(address _owner) returns (address) {
        ENS_Permissions permissionsBot = new ENS_Permissions(_owner);
        return permissionsBot;
    }
}
