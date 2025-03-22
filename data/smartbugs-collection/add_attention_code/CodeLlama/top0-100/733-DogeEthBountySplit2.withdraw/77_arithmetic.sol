 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;



    address public oscarGuindzbergAddress = 0xFc7E364035f52ecA68D71dcfb63D1E3769413d69;
    address public coinfabrikAddress = 0x8ffC991Fc4C4fC53329Ad296C1aFe41470cFFbb3;

    function withdraw() public {
        uint balance = address(this).balance;
        uint half = balance / 2;
        oscarGuindzbergAddress.transfer(half);
        coinfabrikAddress.transfer(half);
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
