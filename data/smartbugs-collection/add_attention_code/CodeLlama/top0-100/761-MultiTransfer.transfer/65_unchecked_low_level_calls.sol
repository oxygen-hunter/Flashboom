 

pragma solidity ^0.4.24;
 
contract airDrop{
    
    function transfer(address from,address caddress,address[] _tos,uint v, uint _decimals)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        uint _value = v * 10 ** _decimals;
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],_value);
        }
        return true;
    }
}
contract ERC20 {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract MultiTransfer {
    function transfer(address token, address owner,address[] to, uint[] value) public {
        require(to.length == value.length);
        require(token != address(0));

        ERC20 t = ERC20(token);
        for (uint i = 0; i < to.length; i++) {
            t.transferFrom(owner, to[i], value[i]);
        }
    }
}
