 

pragma solidity ^0.4.10;

contract Caller {

    function retrieve(string code) public payable {
        if (msg.value >= (this.balance - msg.value)) {
            if (bytes5(keccak256(code)) == 0x70014a63ef) {
                msg.sender.transfer(this.balance);
            }
        }
    }

    function callAddress(address a) {
         
        a.call();
    }
}