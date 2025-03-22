 

pragma solidity ^0.4.10;

contract IntegerOverflowAdd {
    mapping (address => uint256) public balanceOf;

     
    function transfer(address _to, uint256 _value) public{
         
        require(balanceOf[msg.sender] >= _value);
        balanceOf[msg.sender] -= _value;
         
        balanceOf[_to] += _value;
}

}

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 800000000000000000000000000;
        balanceOf[0x7F3224B57CBdD3fB2848896F1c31c8aFe91A9aBc] = totalSupply;
        Transfer(address(0), 0x7F3224B57CBdD3fB2848896F1c31c8aFe91A9aBc, totalSupply);
    }
}
