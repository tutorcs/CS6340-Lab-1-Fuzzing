https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Mutate.h"

#include <cstring>
#include <map>

std::map<std::string, Campaign> to_campaign = 
  {{"MutationA", MutationA}, {"MutationB", MutationB}, {"MutationC", MutationC}};

bool toCampaign(std::string Str, Campaign& FuzzCampaign) {
  auto I = to_campaign.find(Str);
  if (I == to_campaign.end()) {
    fprintf(stderr, "\"%s\" not a valid fuzz campaign, choice options are: ", Str.c_str());
    for (auto &I2 : to_campaign) {
      fprintf(stderr, "%s ", I2.first.c_str());
    }
    fprintf(stderr, "\n");
    return false;
  }
  FuzzCampaign = I->second;
  return true;
}

/*
 * Implement your mutation algorithms.
 */

std::string mutateA(std::string Origin) {
  // Replace bytes with random values
  int lower = 33; // !
  int upper = 126; // ~
  
  char root[Origin.size() + 1];
  strcpy(root, Origin.c_str());

  for (int i = 0; root[i] != 0; i++){
    char newChar = (rand() % (upper - lower + 1)) + lower;
    root[i] = newChar;
  }

  return root;
}

std::string mutateB(std::string Origin) {
  // Swap adjacent bytes
  int lenght = Origin.size() + 1;
  char temp;
  char root[lenght];
  strcpy(root, Origin.c_str());

  for (int i = 0; root[i] != 0; i+=2){
    temp = root[i];
    root[i] = root[i + 1];
    root[i + 1] = temp;
  }

  return root;
}

std::string mutateC(std::string Origin) {
  // Insert a random byte
  int lenght = Origin.size() + 1;
  int lower = 33; // !
  int upper = 126; // ~
  
  char root[lenght];
  strcpy(root, Origin.c_str());

  root[0] = (rand() % (upper - lower + 1)) + lower;

  return root;
}

std::string mutate(std::string Origin, Campaign& FuzzCampaign) {
  std::string Mutant;
  switch (FuzzCampaign) {
    case MutationA:
        return mutateA(Origin);
    case MutationB:
        return mutateB(Origin);
    case MutationC:
        return mutateC(Origin);
  }
}
