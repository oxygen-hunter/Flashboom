 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
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
