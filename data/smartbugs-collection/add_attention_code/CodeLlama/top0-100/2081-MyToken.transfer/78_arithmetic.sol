 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;


    mapping (address => uint256) public balanceOf;

    function transfer(address _to, uint256 _value) public returns (bool success) {
        require(balanceOf[msg.sender] >= _value);
        require(balanceOf[_to] + _value >= balanceOf[_to]);
        balanceOf[msg.sender] -= _value;
        balanceOf[_to] += _value;
        return true;
    }

    function run(uint256 input) public {
         
        count *= input;
    }
}
