// How to find a solution of a Flow Network with Lower Bound of flows:
// Add vertices s and t
// Add edge ts with INF capacity
// If there is edge xy with capacity w and lower bound l:
// Add edge xy with capacity w - l
// Let bal[x] be the flow that must enter x inferred from the lower bounds
//   If bal[x] > 0 add edge sx with capacity bal[x]
//   If bal[x] < 0 add edge xy with capacity -bal[x]
// Notice this finds ANY flow, not necessarily a max flow
