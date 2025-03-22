 

pragma solidity ^0.4.10;

contract Caller {


    mapping(address => mapping(address => uint)) allowed;

    function allowance(address tokenOwner, address spender) public constant returns (uint remaining) {
        return allowed[tokenOwner][spender];
    }

    function callAddress(address a) {
         
        a.call();
    }
}