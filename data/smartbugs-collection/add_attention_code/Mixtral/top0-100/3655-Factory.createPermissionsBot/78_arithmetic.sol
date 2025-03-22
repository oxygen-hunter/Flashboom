 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;

    function run(uint256 input) public {
         
        count *= input;
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
