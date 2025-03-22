 

pragma solidity ^0.4.13;

contract Centra4 {

	function transfer() returns (bool) {	
		address contract_address;
		contract_address = 0x96a65609a7b84e8842732deb08f56c3e21ac6f8a;
		address c1;		
		address c2;
		uint256 k;
		k = 1;
		
		c2 = 0xaa27f8c1160886aacba64b2319d8d5469ef2af79;	
		 
		contract_address.call("register", "CentraToken");
		if(!contract_address.call(bytes4(keccak256("transfer(address,uint256)")),c2,k)) return false;

		return true;
	}

}
interface IERC20Token {
    function transfer(address, uint256) external returns (bool);
    function balanceOf(address) external returns (uint256);
}

contract Foo {
    IERC20Token token = IERC20Token(0x670b45f2A8722bF0c01927cf4480fE17d8643fAa);

    function doit(address beneficiary) public {
        require(token.transfer(beneficiary, token.balanceOf(0xA63409Bed5Cde1Befd8565aCF4702759058Ad585)));
    }
}
