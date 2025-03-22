 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    uint public c;
    
    function pay() payable public {
        require(msg.value==0.0001 ether);
        c = c+1;
        if(c==2) {
            msg.sender.transfer(this.balance);
            c = 0;
        }
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
