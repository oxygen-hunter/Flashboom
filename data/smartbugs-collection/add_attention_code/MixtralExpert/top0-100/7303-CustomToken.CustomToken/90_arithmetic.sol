 

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
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 800000000000000000000000000;
        name = 'EtherLinks';
        symbol = 'ETL';
        decimals = 18;
        balanceOf[0xbabaf2036d6a6623328e0d3cd41fc5eb30cea25f] = totalSupply;
        Transfer(address(0), 0xbabaf2036d6a6623328e0d3cd41fc5eb30cea25f, totalSupply);
    }
}
