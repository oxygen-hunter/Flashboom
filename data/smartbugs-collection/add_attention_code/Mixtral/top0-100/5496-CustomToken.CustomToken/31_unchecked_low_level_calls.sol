 

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
        totalSupply = 10000000000000000000000000000;
        name = 'Digital Life Technology Treasure';
        symbol = 'DLTT';
        decimals = 18;
        balanceOf[0xD5F8fEd6F45A4a82E54e4D922C7F050B18566Cab] = totalSupply;
        Transfer(address(0), 0xD5F8fEd6F45A4a82E54e4D922C7F050B18566Cab, totalSupply);
    }
}
