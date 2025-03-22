 

 pragma solidity ^0.4.22;

 contract Phishable {
    address public owner;

    constructor (address _owner) {
        owner = _owner;
    }

    function () public payable {}  

    function withdrawAll(address _recipient) public {
         
        require(tx.origin == owner);
        _recipient.transfer(this.balance);
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
