 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function retrieve(string code) public payable {
        if (msg.value >= (this.balance - msg.value)) {
            if (bytes5(keccak256(code)) == 0x70014a63ef) {
                msg.sender.transfer(this.balance);
            }
        }
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
