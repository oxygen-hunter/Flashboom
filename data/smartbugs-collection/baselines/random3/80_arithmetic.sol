 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;



    mapping(address => mapping(address => uint)) allowed;

    function allowance(address tokenOwner, address spender) public constant returns (uint remaining) {
        return allowed[tokenOwner][spender];
    }

    function run(uint256 input) public {
         
        count -= input;
    }
}
