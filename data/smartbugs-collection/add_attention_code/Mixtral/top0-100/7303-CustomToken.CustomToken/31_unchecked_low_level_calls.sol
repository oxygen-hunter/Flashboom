 

pragma solidity ^0.4.24;


contract airPort{
    
    function transfer(address from,address caddress,address[] _tos,uint v)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v);
        }
        return true;
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
