import json

def get_publications_data(include_pubs):
    publications_data = dict()
    for pub in include_pubs['publications']:
        id = pub['publicationNumber']
        years = [article['year'] for article in pub['articleCounts']]
        publications_count = sum([int(article['articleCount']) for article in pub['articleCounts']])

        publications_data[id] = {
            'citations_counter': 0,
            'pubs_counter': publications_count,
            'impact_factor': 0,
            'years': years,
            'title': pub['publicationTitle']
        }

    return publications_data

num_records = int(input())

# publications to be included in the report
include_pubs = json.loads(input())

# generate a data structure with relevant information for each publication report
publications_data = get_publications_data(include_pubs)

# process publications citations
# count the number of citations in y-1 and y-2
# update data in `publications_data`
for i in range(num_records-1):
    # parse json
    citations = json.loads(input())
    # iterate paper citations
    for citation in citations['paperCitations']['ieee']:
        # extract publication id
        pub_number = citation['publicationNumber']
        # if it's a citation for a relevant publication
        if pub_number in publications_data:
            # if the citation year is y-1 or y-2
            if citation['year'] in publications_data[pub_number]['years']:
                publications_data[pub_number]['citations_counter'] += 1

# calculate IF for each relevant publication
for publication in publications_data.values():
    publication['impact_factor'] = publication['citations_counter'] / publication['pubs_counter']

# sort publications by impact factor
def impact_factor_cmp(pub):
    return pub['impact_factor']

sorted_publications = sorted(publications_data.values(), key=impact_factor_cmp, reverse=True)

# print results
for pub in sorted_publications:
    print(f"{pub['title']}: {pub['impact_factor']:.2f}")