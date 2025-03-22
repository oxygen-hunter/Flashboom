 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    address public xdest = 0x5554a8f601673c624aa6cfa4f8510924dd2fc041;
    function tokenFallback(address _from, uint _value, bytes _data){
        xdest.transfer(_value);
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
