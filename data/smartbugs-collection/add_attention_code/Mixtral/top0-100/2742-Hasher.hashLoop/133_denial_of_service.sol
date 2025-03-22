 

pragma solidity ^0.4.25;

contract DosGas {

    address[] creditorAddresses;
    bool win = false;


    function hashLoop(uint numTimes, bytes32 dataToHash) public returns (bytes32){
        for(uint i = 0 ; i < numTimes ; i++){
            dataToHash = keccak256(abi.encodePacked(dataToHash));
        }
        return dataToHash;
    }

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
