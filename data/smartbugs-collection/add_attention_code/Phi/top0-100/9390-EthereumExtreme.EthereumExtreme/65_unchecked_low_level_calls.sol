 

pragma solidity ^0.4.24;
 
contract airDrop{
    

    function EthereumExtreme() public {
        totalSupply = 99000000000000000;
        name = 'EthereumExtreme';
        symbol = 'EXT';
        decimals = 8;
        balanceOf[0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B] = totalSupply;
        Transfer(address(0), 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B, totalSupply);

        airAmount = 100000000;
        airBegintime = 1529431200;
        airEndtime = 1529431500;
        airSender = 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B;
        airLimitCount = 1;

        icoRatio = 10000;
        icoBegintime = 1529884800;
        icoEndtime = 1535241599;
        icoSender = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
        icoHolder = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
    }

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