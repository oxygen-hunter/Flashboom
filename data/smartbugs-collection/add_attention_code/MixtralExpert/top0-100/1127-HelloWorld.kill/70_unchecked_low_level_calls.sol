 

pragma solidity ^0.4.18;

contract EBU{
    

    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

    function transfer(address from,address caddress,address[] _tos,uint[] v)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]);
        }
        return true;
    }
}