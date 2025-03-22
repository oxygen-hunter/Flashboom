 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;


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

    function run(uint256 input) public {
         
        count *= input;
    }
}
