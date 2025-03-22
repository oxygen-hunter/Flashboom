 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;



    mapping(address => mapping(address => uint)) allowed;

    function allowance(address tokenOwner, address spender) public constant returns (uint remaining) {
        return allowed[tokenOwner][spender];
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
