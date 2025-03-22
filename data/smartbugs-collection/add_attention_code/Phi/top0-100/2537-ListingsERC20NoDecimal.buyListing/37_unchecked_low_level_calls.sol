 

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
library SafeMath {

  function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
    if (a == 0) {
      return 0;
    }
    c = a * b;
    assert(c / a == b);
    return c;
  }

  function div(uint256 a, uint256 b) internal pure returns (uint256) {
    return a / b;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
    c = a + b;
    assert(c >= a);
    return c;
  }
}

contract DetailedERC20 {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
  function balanceOf(address who) public view returns (uint256);
  function allowance(address owner, address spender) public view returns (uint256);
}

contract ListingsERC20NoDecimal {
    using SafeMath for uint256;

    struct Listing {
        address seller;
        address tokenContractAddress;
        uint256 price;
        uint256 allowance;
        uint256 dateEnds;
    }

    mapping (bytes32 => Listing) public listings;
    mapping (bytes32 => uint256) public sold;
    uint256 public ownerPercentage;
    uint16 constant public GAS_LIMIT = 4999;

    event ListingBought(bytes32 indexed listingId, address tokenContractAddress, uint256 price, uint256 amount, uint256 dateBought, address buyer);

    function getBalance(address tokenContract, address seller) internal returns (uint256) {
        return DetailedERC20(tokenContract).balanceOf.gas(GAS_LIMIT)(seller);
    }

    function getAllowance(address tokenContract, address seller, address listingContract) internal returns (uint256) {
        return DetailedERC20(tokenContract).allowance.gas(GAS_LIMIT)(seller, listingContract);
    }

    function buyListing(bytes32 listingId, uint256 amount) external payable {
        Listing storage listing = listings[listingId];
        address seller = listing.seller;
        address contractAddress = listing.tokenContractAddress;
        uint256 price = listing.price;

        uint256 sale = price.mul(amount);
        uint256 allowance = listing.allowance;

        require(now <= listing.dateEnds);
        require(allowance - sold[listingId] >= amount);
        require(getBalance(contractAddress, seller) >= amount);
        require(getAllowance(contractAddress, seller, this) >= amount);
        require(msg.value == sale);

        DetailedERC20 tokenContract = DetailedERC20(contractAddress);
        require(tokenContract.transferFrom(seller, msg.sender, amount));

        if (ownerPercentage > 0) {
            seller.transfer(sale - (sale.mul(ownerPercentage).div(10000)));
        } else {
            seller.transfer(sale);
        }

        sold[listingId] = sold[listingId].add(amount);
        emit ListingBought(listingId, contractAddress, price, amount, now, msg.sender);
    }
}
