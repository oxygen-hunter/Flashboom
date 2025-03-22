 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
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
