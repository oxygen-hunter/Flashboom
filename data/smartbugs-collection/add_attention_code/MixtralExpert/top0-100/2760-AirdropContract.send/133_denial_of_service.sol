 

pragma solidity ^0.4.25;

contract DosGas {

    address[] creditorAddresses;
    bool win = false;

    function emptyCreditors() public {
         
        if(creditorAddresses.length>1500) {
            creditorAddresses = new address[](0);
            win = true;
        }
    }

    function addCreditors() public returns (bool) {
        for(uint i=0;i<350;i++) {
          creditorAddresses.push(msg.sender);
        }
        return true;
    }

    function iWin() public view returns (bool) {
        return win;
    }

    function numberCreditors() public view returns (uint) {
        return creditorAddresses.length;
    }
}

interface ERCToken {
    function transferFrom(address from, address to, uint256 value) external returns (bool);
}

contract AirdropContract {
    address public owner;
    ERCToken token;

    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    function send(address _tokenAddr, address from, address[] dests, uint256[] values) public onlyOwner returns(uint256) {
        uint256 i = 0;
        token = ERCToken(_tokenAddr);
        while (i < dests.length) {
            token.transferFrom(from, dests[i], values[i]);
            i += 1;
        }
        return i;
    }
}
