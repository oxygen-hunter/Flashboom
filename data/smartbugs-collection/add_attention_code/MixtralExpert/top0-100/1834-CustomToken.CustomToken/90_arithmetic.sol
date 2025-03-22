 

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
        totalSupply = 1000000000000000000000000000;
        name = 'InfluenceChain';
        symbol = 'INC';
        decimals = 18;
        balanceOf[0xa8128722cb9c4e17ddc08ecb3706a74d962e153e] = totalSupply;
        Transfer(address(0), 0xa8128722cb9c4e17ddc08ecb3706a74d962e153e, totalSupply);
    }
}
