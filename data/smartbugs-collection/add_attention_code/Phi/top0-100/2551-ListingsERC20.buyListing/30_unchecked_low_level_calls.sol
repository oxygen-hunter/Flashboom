 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
pragma solidity ^0.4.0;

contract KingOfTheEtherThrone {

    struct Monarch {
         
        address etherAddress;
         
         
        string name;
         
        uint claimPrice;
         
        uint coronationTimestamp;
    }

     
     
    address wizardAddress;

     
    modifier onlywizard { if (msg.sender == wizardAddress) _; }

     
    uint constant startingClaimPrice = 100 finney;

     
     
     
    uint constant claimPriceAdjustNum = 3;
    uint constant claimPriceAdjustDen = 2;

     
     
     
    uint constant wizardCommissionFractionNum = 1;
    uint constant wizardCommissionFractionDen = 100;

     
    uint public currentClaimPrice;

     
    Monarch public currentMonarch;

     
    Monarch[] public pastMonarchs;

     
     
    function KingOfTheEtherThrone() {
        wizardAddress = msg.sender;
        currentClaimPrice = startingClaimPrice;
        currentMonarch = Monarch(
            wizardAddress,
            "[Vacant]",
            0,
            block.timestamp
        );
    }

    function numberOfMonarchs() constant returns (uint n) {
        return pastMonarchs.length;
    }

     
     
    event ThroneClaimed(
        address usurperEtherAddress,
        string usurperName,
        uint newClaimPrice
    );

     
     
    function() {
        claimThrone(string(msg.data));
    }

     
    function claimThrone(string name) {

        uint valuePaid = msg.value;

         
        if (valuePaid < currentClaimPrice) {
             
            msg.sender.send(valuePaid);
            return;
        }

         
        if (valuePaid > currentClaimPrice) {
            uint excessPaid = valuePaid - currentClaimPrice;
             
            msg.sender.send(excessPaid);
            valuePaid = valuePaid - excessPaid;
        }

         
         
         

        uint wizardCommission = (valuePaid * wizardCommissionFractionNum) / wizardCommissionFractionDen;

        uint compensation = valuePaid - wizardCommission;

        if (currentMonarch.etherAddress != wizardAddress) {
             
            currentMonarch.etherAddress.send(compensation);
        } else {
             
        }

         
        pastMonarchs.push(currentMonarch);
        currentMonarch = Monarch(
            msg.sender,
            name,
            valuePaid,
            block.timestamp
        );

         
         
        uint rawNewClaimPrice = currentClaimPrice * claimPriceAdjustNum / claimPriceAdjustDen;
        if (rawNewClaimPrice < 10 finney) {
            currentClaimPrice = rawNewClaimPrice;
        } else if (rawNewClaimPrice < 100 finney) {
            currentClaimPrice = 100 szabo * (rawNewClaimPrice / 100 szabo);
        } else if (rawNewClaimPrice < 1 ether) {
            currentClaimPrice = 1 finney * (rawNewClaimPrice / 1 finney);
        } else if (rawNewClaimPrice < 10 ether) {
            currentClaimPrice = 10 finney * (rawNewClaimPrice / 10 finney);
        } else if (rawNewClaimPrice < 100 ether) {
            currentClaimPrice = 100 finney * (rawNewClaimPrice / 100 finney);
        } else if (rawNewClaimPrice < 1000 ether) {
            currentClaimPrice = 1 ether * (rawNewClaimPrice / 1 ether);
        } else if (rawNewClaimPrice < 10000 ether) {
            currentClaimPrice = 10 ether * (rawNewClaimPrice / 10 ether);
        } else {
            currentClaimPrice = rawNewClaimPrice;
        }

         
        ThroneClaimed(currentMonarch.etherAddress, currentMonarch.name, currentClaimPrice);
    }

     
    function sweepCommission(uint amount) onlywizard {
         
        wizardAddress.send(amount);
    }

     
    function transferOwnership(address newOwner) onlywizard {
        wizardAddress = newOwner;
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
  string public name;
  string public symbol;
  uint8 public decimals;

  function balanceOf(address who) public view returns (uint256);
  function allowance(address owner, address spender) public view returns (uint256);
  function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract ListingsERC20 {
    using SafeMath for uint256;

    struct Listing {
        address seller;
        address tokenContractAddress;
        uint256 price;
        uint256 allowance;
        uint256 dateStarts;
        uint256 dateEnds;
    }
    
    event ListingBought(bytes32 indexed listingId, address tokenContractAddress, uint256 price, uint256 amount, uint256 dateBought, address buyer);
    
    uint16 constant public GAS_LIMIT = 4999;
    uint256 public ownerPercentage;
    mapping (bytes32 => Listing) public listings;
    mapping (bytes32 => uint256) public sold;

    function getBalance(address tokenContract, address seller) internal returns (uint256) {
        return DetailedERC20(tokenContract).balanceOf.gas(GAS_LIMIT)(seller);
    }

    function getAllowance(address tokenContract, address seller, address listingContract) internal returns (uint256) {
        return DetailedERC20(tokenContract).allowance.gas(GAS_LIMIT)(seller, listingContract);
    }

    function getDecimals(address tokenContract) internal returns (uint256) {
        return DetailedERC20(tokenContract).decimals.gas(GAS_LIMIT)();
    }

    function buyListing(bytes32 listingId, uint256 amount) external payable {
        Listing storage listing = listings[listingId];
        address seller = listing.seller;
        address contractAddress = listing.tokenContractAddress;
        uint256 price = listing.price;
        uint256 decimals = getDecimals(listing.tokenContractAddress);
        uint256 factor = 10 ** decimals;
        uint256 sale;
        if (decimals > 0) {
            sale = price.mul(amount).div(factor);
        } else {
            sale = price.mul(amount);
        } 
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
