 

pragma solidity ^0.4.10;

contract IntegerOverflowAdd {
    mapping (address => uint256) public balanceOf;

     

    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function transfer(address _to, uint256 _value) public{
         
        require(balanceOf[msg.sender] >= _value);
        balanceOf[msg.sender] -= _value;
         
        balanceOf[_to] += _value;
}

}
